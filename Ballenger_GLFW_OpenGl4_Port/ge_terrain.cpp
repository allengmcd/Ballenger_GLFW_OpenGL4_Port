#include "ge_terrain.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Magick++.h>

Terrain::Terrain(){}

Terrain::~Terrain(){}

Vector cross(Vector a, Vector b)
{
	Vector vec;
	vec.x = a.y*b.z - a.z*b.y;
	vec.y = a.z*b.x - a.x*b.z;
	vec.z = a.x*b.y - a.y*b.x;

	return vec;
}

bool fcompare(Vector a, Vector b) { return (abs(a.y) > abs(b.y)); }

void Terrain::ComputeTriangle(std::vector<Coord> &triangle)
{
	Triangle tri;

	//me guardo los vertices del triangulo
	tri.vertexs[0] = triangle[0];
	tri.vertexs[1] = triangle[1];
	tri.vertexs[2] = triangle[2];

	//calculo el baricentro
	tri.barycenter.x = (triangle[0].x + triangle[1].x + triangle[2].x)/3;
	tri.barycenter.y = (triangle[0].y + triangle[1].y + triangle[2].y)/3;
	tri.barycenter.z = (triangle[0].z + triangle[1].z + triangle[2].z)/3;

	//calculo el vector unitario de la normal
	Vector a,b;
	if(triangles.size()%2 != 0) std::swap(triangle[2],triangle[0]);
	a.x = triangle[1].x - triangle[0].x;
	a.y = triangle[1].y - triangle[0].y;
	a.z = triangle[1].z - triangle[0].z;

	b.x = triangle[2].x - triangle[1].x;
	b.y = triangle[2].y - triangle[1].y;
	b.z = triangle[2].z - triangle[1].z;
	if(triangles.size()%2 != 0) std::swap(triangle[2],triangle[0]);

	Vector aux = cross(a,b);
	float factor = sqrt( 1.0f/(aux.x*aux.x + aux.y*aux.y + aux.z*aux.z) );
	aux.x *= factor;
	aux.y *= factor;
	aux.z *= factor;
	tri.N = aux;

	triangles.push_back(tri);
	std::swap(triangle[1],triangle[0]);
	std::swap(triangle[2],triangle[1]);
	triangle.pop_back();
}

Vector Terrain::SetNormalPerVertex(int x,float y,int z)
{
	Vector X,Z,N; X.x = 2.0f; X.z = 0.0f; Z.x = 0.0f; Z.z = 2.0f;
	float left_y, right_y, up_y, down_y;
	
	if(x == 0)
	{
		left_y  = y;
		right_y = heightmap2[z * TERRAIN_SIZE + (x+1)] / SCALE_FACTOR;
	}
	else if(x == TERRAIN_SIZE-1)
	{
		left_y  = heightmap2[z * TERRAIN_SIZE + (x-1)] / SCALE_FACTOR;
		right_y = y;
	}
	else
	{
		left_y  = heightmap2[z * TERRAIN_SIZE + (x-1)] / SCALE_FACTOR;
		right_y = heightmap2[z * TERRAIN_SIZE + (x+1)] / SCALE_FACTOR;
	}

	if(z == 0)
	{
		up_y   = y;
		down_y = heightmap2[(z+1) * TERRAIN_SIZE + x] / SCALE_FACTOR;
	}
	else if(z == TERRAIN_SIZE-1)
	{
		up_y   = heightmap2[(z-1) * TERRAIN_SIZE + x] / SCALE_FACTOR;
		down_y = y;
	}
	else
	{
		up_y   = heightmap2[(z-1) * TERRAIN_SIZE + x] / SCALE_FACTOR;
		down_y = heightmap2[(z+1) * TERRAIN_SIZE + x] / SCALE_FACTOR;
	}

	X.y = right_y - left_y;
	Z.y = down_y - up_y;

	N = cross(Z,X);
	float factor = sqrt( 1.0f/(N.x*N.x + N.y*N.y + N.z*N.z) );
	N.x *= factor; N.y *= factor; N.z *= factor;

	//glNormal3f(N.x,N.y,N.z);
	return N;
}

void Terrain::Load(int level, Shader *Shader, Data *Data)
{
	Magick::InitializeMagick("");

	// Magick::Image level_map;
	data = Data;
	shader = Shader;
	std::cout << "Loading Terrain, level: " << level << std::endl;

	triangles.clear();

	char file[32];
	if(level<10) sprintf(file,"Levels/terrain0%d.raw",level);
	else		 sprintf(file,"Levels/terrain%d.raw",level);
	FILE *pFile = fopen(file, "rb");
	std::cout << "Terrain fread" << std::endl;

	int terrainReturnSize = fread(heightmap,TERRAIN_SIZE * TERRAIN_SIZE,sizeof(GLubyte),pFile); 
	
	
	std::cout << "Terrain check, terrainReturnSize: " << terrainReturnSize << std::endl;
	if(terrainReturnSize != (TERRAIN_SIZE * TERRAIN_SIZE))
	{
		std::cout << "An error occurred while reading in terrain file" << std::endl;
	}

	std::cout << "Terrain fclose" << std::endl;
	fclose(pFile);

	std::cout << "fclose Terrain finish" << std::endl;



	Magick::InitializeMagick("");

	Magick::Image level_map;
    // Read a file into image object 
    level_map.read( "../../../../Levels/level03.jpg" );

	int map_width = level_map.columns();
	int map_height = level_map.rows();

	// get a "pixel cache" for the entire image

	for(int column = 0; column < map_width; column++)
	{
		for(int row = 0; row < map_height; row++)
		{
			Magick::ColorRGB pixel_color = level_map.pixelColor( column, row );

			float greyscale = (pixel_color.red() + pixel_color.green() + pixel_color.blue())/3;
			heightmap2[row * TERRAIN_SIZE + column] = greyscale*255;
		}
	}


	// for(int i = 0; i < TERRAIN_SIZE*TERRAIN_SIZE; i++)
	// {
	// 	float height1 = (float)heightmap[i];
	// 	if((heightmap2[i]+6 < height1 || heightmap2[i]-6 > height1))
	// 	{
	// 		std::cout << heightmap2[i] << " : " << height1 << std::endl;
	// 	}
	// }


	// std::cout << "test1" << std::endl;
	// std::ofstream out("out.txt");
    // std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    // std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!


	// id_Terrain=glGenLists(1);
	// glNewList(id_Terrain,GL_COMPILE);
	unsigned int bufferCounter = 0;
	for (int z = 0; z <TERRAIN_SIZE-1 ; z++)
	{
		std::vector<Coord> triangle(0);
		Coord vertex;

		// glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x < TERRAIN_SIZE; x++)
		{
			// render two vertices of the strip at once
			float scaledHeight = heightmap2[z * TERRAIN_SIZE + x] / SCALE_FACTOR;
			float nextScaledHeight = heightmap2[(z + 1) * TERRAIN_SIZE + x] / SCALE_FACTOR;

			// std::cout << "bufferCounter: " << bufferCounter <<  "         x: " << x << "         z: " << z << "          scaledHeight: " << scaledHeight << "     nextScaledHeight: " << nextScaledHeight << std::endl;

			Vector normalScaledHeight = SetNormalPerVertex(x, scaledHeight, z); //glNormal3f(N.x,N.y,N.z);

			terrainBuffer[bufferCounter++] = x;
			terrainBuffer[bufferCounter++] = scaledHeight;
			terrainBuffer[bufferCounter++] = z;
			terrainBuffer[bufferCounter++] = normalScaledHeight.x;
			terrainBuffer[bufferCounter++] = normalScaledHeight.y;
			terrainBuffer[bufferCounter++] = normalScaledHeight.z;
			terrainBuffer[bufferCounter++] = (float)x/TERRAIN_SIZE*64;
			terrainBuffer[bufferCounter++] = (float)z/TERRAIN_SIZE*64;

			// glTexCoord2f((float)x/TERRAIN_SIZE*64, (float)z/TERRAIN_SIZE*64);
			// Vector normalScaledHeight = SetNormalPerVertex(x, scaledHeight, z); //glNormal3f(N.x,N.y,N.z);
			// glVertex3f(x, scaledHeight, z);
			vertex.x=x; vertex.y=scaledHeight; vertex.z=z;
			triangle.push_back(vertex);
			if(triangle.size() == 3) ComputeTriangle(triangle);


			normalScaledHeight = SetNormalPerVertex(x, scaledHeight, z+1); //glNormal3f(N.x,N.y,N.z);

			terrainBuffer[bufferCounter++] = x;
			terrainBuffer[bufferCounter++] = nextScaledHeight;
			terrainBuffer[bufferCounter++] = z+1;
			terrainBuffer[bufferCounter++] = normalScaledHeight.x;
			terrainBuffer[bufferCounter++] = normalScaledHeight.y;
			terrainBuffer[bufferCounter++] = normalScaledHeight.z;
			terrainBuffer[bufferCounter++] = (float)x/TERRAIN_SIZE*64;
			terrainBuffer[bufferCounter++] = ((float)z+1)/TERRAIN_SIZE*64;
			//bufferCounter++;

			// glTexCoord2f((float)x/TERRAIN_SIZE*64, (float)(z + 1)/TERRAIN_SIZE*64);
			// Vector normalScaledHeight = SetNormalPerVertex(x, scaledHeight, (z + 1)); // 
			// glVertex3f(x, nextScaledHeight, (z + 1));
			vertex.x=x; vertex.y=nextScaledHeight; vertex.z=z+1;
			triangle.push_back(vertex);
			if(triangle.size() == 3) ComputeTriangle(triangle);
		}
		// glEnd();
	}
	// glEndList();


	// int i = 0;
	// while(i < ((TERRAIN_SIZE * (TERRAIN_SIZE-1))*(3+3+2)*2))
	// {
	// 	std::cout << "i: " << i << "; ";
	// 	std::cout << " " << terrainBuffer[i++];
	// 	std::cout << " " << terrainBuffer[i++];
	// 	std::cout << " " << terrainBuffer[i++];
	// 	std::cout << " " << terrainBuffer[i++];
	// 	std::cout << " " << terrainBuffer[i++];
	// 	std::cout << " " << terrainBuffer[i++];
	// 	std::cout << " " << terrainBuffer[i++];
	// 	std::cout << " " << terrainBuffer[i++];
	// 	std::cout << std::endl;
	// }
	// std::cout << "test2" << std::endl;

	// int i = 0;
	// while(i < 288)
	// {
	// 	if(cubeVertices[i]== 1.0f || cubeVertices[i] == 0.0f)
	// 	{

	// 	}
	// 	else{
	// 		terrainBuffer[i] = cubeVertices[i]*100;
	// 	}
		
	// 	i++;
	// }




    glGenVertexArrays(1, &terrainVAO);
    glGenBuffers(1, &terrainVBO);

    glBindVertexArray(terrainVAO);
    glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);

	//glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(terrainBuffer), terrainBuffer, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);

    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(terrainVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));




	//glBindVertexArray(terrainVAO);





	// id_Normals=glGenLists(1);
	// glNewList(id_Normals,GL_COMPILE);
	// glLineWidth(1.0);
	// glColor3f(0.5, 0.5, 1.0);
	for(unsigned int i=0; i<triangles.size(); i++)
	{
		// glBegin(GL_LINES);
		// glVertex3f(triangles[i].barycenter.x, triangles[i].barycenter.y, triangles[i].barycenter.z);
		// glVertex3f(triangles[i].barycenter.x + triangles[i].N.x, triangles[i].barycenter.y + triangles[i].N.y, triangles[i].barycenter.z + triangles[i].N.z);
		// glEnd();
	}
	// glColor3f(1.0,1.0,1.0);
	// glEndList();
}

void Terrain::Draw(Camera *camera)
{
	char texture1[] = "texture1\0";
	char texture2[] = "texture2\0";

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view =  camera->GetViewMatrix(); // remove translation from the view matrix
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)camera->SCR_WIDTH/(float)camera->SCR_HEIGHT, 0.1f, 1000.0f);
	// char tex_top[] = "tex_top\0";
	// char tex_side[] = "tex_side\0";

	// glActiveTexture(GL_TEXTURE0);
	// glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_GRASS));
	// glActiveTexture(GL_TEXTURE1);
	// glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_ROCK));

	// shader->Activate(PROGRAM_SIMPLE_TERRAIN);
	// shader->SetUniform(tex_top, 0);
	// shader->SetUniform(tex_side, 1);
	// glDrawArrays(GL_TRIANGLES, 0, ((TERRAIN_SIZE * TERRAIN_SIZE)*(3+3+2)*2));
	// shader->Deactivate();

        glBindVertexArray(terrainVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_GRASS));
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_ROCK));
		shader->Activate(PROGRAM_TERRAIN);
		shader->setInt(texture1, 0);
		shader->setInt(texture2, 1);
		shader->setMat4("model", model);
		shader->setMat4("view", view);
		shader->setMat4("projection", projection);
		shader->setMat4("projection", projection);
		shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader->setVec3("lightPos", glm::vec3(50.0f, 50.0f, 50.0f));
		shader->setVec3("viewPos", camera->Position);

		for(int x = 0; x < 1024;x++)
		{
        	glDrawArrays(GL_TRIANGLE_STRIP, x*1024*2, 1024*2);
		}

        glBindVertexArray(0);
		//shader->Deactivate();
}

float Terrain::GetVertexHeigh(int x, int z)
{
	return heightmap2[(int)z * TERRAIN_SIZE + (int)x] / SCALE_FACTOR;
}

float Terrain::GetHeight(float x,float z)
{
	if(x < 0 || x > TERRAIN_SIZE-1 || z < 0 || z > TERRAIN_SIZE-1) return 0.0f;
	else
	{
		int intx, intz;
		float fracx, fracz, height;

		intx = (int)x;
		intz = (int)z;

		fracx = fmod(x,1);
		fracz = fmod(z,1);
		
		if(x == (float)intx && z == (float)intz) return GetVertexHeigh(intx, intz);
		if(x == (float)intx) return GetVertexHeigh(intx, intz)*(1-fracz) + GetVertexHeigh(intx, intz+1)*fracz;
		if(z == (float)intz) return GetVertexHeigh(intx, intz)*(1-fracx) + GetVertexHeigh(intx+1, intz)*fracx;

		if(fracz == 1.0f - fracx) //esta en la interseccion entre triangulos de una cuatripleta de vertices
		{
			return GetVertexHeigh(intx+1, intz)*(fracz/sin(45.0f)) + GetVertexHeigh(intx, intz+1)*(1-fracz/sin(45.0f));
		}
		if(fracz < 1.0f - fracx) //esta dentro del primer triangulo de la cuatripleta de vertices
		{
			height = GetVertexHeigh(intx, intz)*(1-fracx) + GetVertexHeigh(intx+1, intz)*fracx;
			return height*(1-fracz) + GetVertexHeigh(intx, intz+1)*fracz;
		}
		if(fracz > 1.0f - fracx) //esta dentro del segundo triangulo de la cuatripleta de vertices
		{
			height = GetVertexHeigh(intx, intz+1)*(1-fracx) + GetVertexHeigh(intx+1, intz+1)*fracx;
			return height*fracz + GetVertexHeigh(intx+1, intz)*(1-fracz);
		}
		return 0.0f;
	}
}

bool Terrain::IsColliding(Coord P, float radius, Triangle tri,Coord &center)
{
	Coord Q;  Q.x = P.x + radius*(-tri.N.x);  Q.y = P.y + radius*(-tri.N.y);  Q.z = P.z + radius*(-tri.N.z);
	Vector V;  V.x = Q.x - P.x;  V.y = Q.y - P.y;  V.z = Q.z - P.z;
	float D = -(tri.N.x*tri.vertexs[0].x + tri.N.y*tri.vertexs[0].y + tri.N.z*tri.vertexs[0].z);
	float lambda = -(tri.N.x*P.x + tri.N.y*P.y + tri.N.z*P.z + D) / (tri.N.x*V.x + tri.N.y*V.y + tri.N.z*V.z);

	if(lambda > 1.0f) return false; //si la distancia hasta el plano es insuficiente no colisionara
	Coord I;  I.x = P.x + lambda*V.x;  I.y = P.y + lambda*V.y;  I.z = P.z + lambda*V.z; //punto interseccion

	//comprobamos si el punto interseccion pertenece al triangulo
	float tri_orientation = (tri.vertexs[0].x - tri.vertexs[2].x) * (tri.vertexs[1].z - tri.vertexs[2].z) - (tri.vertexs[0].z - tri.vertexs[2].z) * (tri.vertexs[1].x - tri.vertexs[2].x);
	float ABIor = (tri.vertexs[0].x - I.x) * (tri.vertexs[1].z - I.z) - (tri.vertexs[0].z - I.z) * (tri.vertexs[1].x - I.x);
	float BCIor = (tri.vertexs[1].x - I.x) * (tri.vertexs[2].z - I.z) - (tri.vertexs[1].z - I.z) * (tri.vertexs[2].x - I.x);
	float CAIor = (tri.vertexs[2].x - I.x) * (tri.vertexs[0].z - I.z) - (tri.vertexs[2].z - I.z) * (tri.vertexs[0].x - I.x);
	if( tri_orientation >= 0.0f && (ABIor < 0.0f  || BCIor < 0.0f || CAIor < 0.0f) ) return false;
	if( tri_orientation < 0.0f && (ABIor >= 0.0f  || BCIor >= 0.0f || CAIor >= 0.0f) ) return false;
	
	//llegado a este punto ya sabemos que colisionara con el triangulo tri
	//ahora recalculamos la posicion del centro para dejar la esfera sobre la superficie de tri
	float factor = sqrt( (radius*radius)/(tri.N.x*tri.N.x + tri.N.y*tri.N.y + tri.N.z*tri.N.z) );
	center.x = I.x + tri.N.x*factor;
	center.y = I.y + tri.N.y*factor;
	center.z = I.z + tri.N.z*factor;

	return true;
}

std::vector<Vector> Terrain::GetCollisionNormals(Coord &center, float radius)
{
	std::vector<Vector> cnormals(0);

	if(center.x < radius || center.x > (float)TERRAIN_SIZE-1.0f-radius || center.z < radius || center.z > (float)TERRAIN_SIZE-1.0f-radius)
	{
		Vector N;
		N.x = 0.0f; N.y = 1.0f; N.z = 0.0f;
		if(center.y <= radius) { center.y = radius; cnormals.push_back(N); }
		return cnormals;
	}
	else
	{
		int intx, intz;
		float fracx, fracz;
		int trianglex, trianglez;
		Coord P; P.x = center.x; P.y = center.y; P.z = center.z;
		Triangle tri;

		intx = (int)center.x;
		intz = (int)center.z;

		fracx = fmod(center.x,1);
		fracz = fmod(center.z,1);
		
		//obtengo la posicion matricial del primer triangulo del quad de vertices en el que esta
		trianglex = intx*2;
		trianglez = intz;

		if(fracx == 0.5f && fracz == 0.5f)
		{
			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex+1];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			sort(cnormals.begin(),cnormals.end(),fcompare);
			return cnormals;
		}
		if(fracx == 0.5f)
		{
			if(fracz < 0.5f)
			{
				tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
				tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex+1];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

				tri = triangles[(trianglez-1)*(TERRAIN_SIZE-1)*2 + trianglex];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
				tri = triangles[(trianglez-1)*(TERRAIN_SIZE-1)*2 + trianglex+1];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

				sort(cnormals.begin(),cnormals.end(),fcompare);
			}
			else
			{
				tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
				tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex+1];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

				tri = triangles[(trianglez+1)*(TERRAIN_SIZE-1)*2 + trianglex];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
				tri = triangles[(trianglez+1)*(TERRAIN_SIZE-1)*2 + trianglex+1];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

				sort(cnormals.begin(),cnormals.end(),fcompare);
			}
			return cnormals;
		}
		if(fracz == 0.5f)
		{
			if(fracx < 0.5f)
			{
				tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
				tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex+1];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

				tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex-2];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
				tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex-1];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

				sort(cnormals.begin(),cnormals.end(),fcompare);
			}
			else
			{
				tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
				tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex+1];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

				tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex+2];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
				tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex+3];
				if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

				sort(cnormals.begin(),cnormals.end(),fcompare);
			}
			return cnormals;
		}
		if(fracx < 0.5 && fracz < 0.5)
		{
			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex+1];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex-2];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex-1];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);


			tri = triangles[(trianglez-1)*(TERRAIN_SIZE-1)*2 + trianglex];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[(trianglez-1)*(TERRAIN_SIZE-1)*2 + trianglex+1];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

			tri = triangles[(trianglez-1)*(TERRAIN_SIZE-1)*2 + trianglex-2];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[(trianglez-1)*(TERRAIN_SIZE-1)*2 + trianglex-1];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

			sort(cnormals.begin(),cnormals.end(),fcompare);
			return cnormals;
		}
		if(fracx > 0.5 && fracz < 0.5)
		{
			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex+1];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex+2];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex+3];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);


			tri = triangles[(trianglez-1)*(TERRAIN_SIZE-1)*2 + trianglex];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[(trianglez-1)*(TERRAIN_SIZE-1)*2 + trianglex+1];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

			tri = triangles[(trianglez-1)*(TERRAIN_SIZE-1)*2 + trianglex+2];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[(trianglez-1)*(TERRAIN_SIZE-1)*2 + trianglex+3];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

			sort(cnormals.begin(),cnormals.end(),fcompare);
			return cnormals;
		}
		if(fracx < 0.5 && fracz > 0.5)
		{
			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex+1];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex-2];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex-1];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);


			tri = triangles[(trianglez+1)*(TERRAIN_SIZE-1)*2 + trianglex];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[(trianglez+1)*(TERRAIN_SIZE-1)*2 + trianglex+1];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

			tri = triangles[(trianglez+1)*(TERRAIN_SIZE-1)*2 + trianglex-2];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[(trianglez+1)*(TERRAIN_SIZE-1)*2 + trianglex-1];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

			sort(cnormals.begin(),cnormals.end(),fcompare);
			return cnormals;
		}
		if(fracx > 0.5 && fracz > 0.5)
		{
			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex+1];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex+2];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[trianglez*(TERRAIN_SIZE-1)*2 + trianglex+3];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);


			tri = triangles[(trianglez+1)*(TERRAIN_SIZE-1)*2 + trianglex];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[(trianglez+1)*(TERRAIN_SIZE-1)*2 + trianglex+1];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

			tri = triangles[(trianglez+1)*(TERRAIN_SIZE-1)*2 + trianglex+2];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);
			
			tri = triangles[(trianglez+1)*(TERRAIN_SIZE-1)*2 + trianglex+3];
			if(IsColliding(P,radius,tri,center)) cnormals.push_back(tri.N);

			sort(cnormals.begin(),cnormals.end(),fcompare);
			return cnormals;
		}
		return cnormals; //never used
	}
}

bool Terrain::IsColliding(Coord P, Coord Q, Triangle tri,float &lambda)
{
	Vector V;  V.x = Q.x - P.x;  V.y = Q.y - P.y;  V.z = Q.z - P.z;
	float D = -(tri.N.x*tri.vertexs[0].x + tri.N.y*tri.vertexs[0].y + tri.N.z*tri.vertexs[0].z);
	if(tri.N.x*V.x + tri.N.y*V.y + tri.N.z*V.z == 0.0f) return false;
	else lambda = -(tri.N.x*P.x + tri.N.y*P.y + tri.N.z*P.z + D) / (tri.N.x*V.x + tri.N.y*V.y + tri.N.z*V.z);

	if(lambda < 0.0f || lambda > 1.0f) return false;
	Coord I;  I.x = P.x + lambda*V.x;  I.y = P.y + lambda*V.y;  I.z = P.z + lambda*V.z; //punto interseccion

	//comprobamos si el punto interseccion pertenece al triangulo
	float tri_orientation = (tri.vertexs[0].x - tri.vertexs[2].x) * (tri.vertexs[1].z - tri.vertexs[2].z) - (tri.vertexs[0].z - tri.vertexs[2].z) * (tri.vertexs[1].x - tri.vertexs[2].x);
	float ABIor = (tri.vertexs[0].x - I.x) * (tri.vertexs[1].z - I.z) - (tri.vertexs[0].z - I.z) * (tri.vertexs[1].x - I.x);
	float BCIor = (tri.vertexs[1].x - I.x) * (tri.vertexs[2].z - I.z) - (tri.vertexs[1].z - I.z) * (tri.vertexs[2].x - I.x);
	float CAIor = (tri.vertexs[2].x - I.x) * (tri.vertexs[0].z - I.z) - (tri.vertexs[2].z - I.z) * (tri.vertexs[0].x - I.x);
	if( tri_orientation >= 0.0f && (ABIor < 0.0f  || BCIor < 0.0f || CAIor < 0.0f) ) return false;
	if( tri_orientation < 0.0f && (ABIor >= 0.0f  || BCIor >= 0.0f || CAIor >= 0.0f) ) return false;

	return true;
}

float Terrain::GetSegmentIntersectionLambda(float x,float y,float z, float vx,float vy,float vz, float dist)
{
	Coord P; P.x = x; P.y = y;  P.z = z;
	Coord Q; Q.x = x - dist*vx; Q.y = y - dist*vy; Q.z = z - dist*vz;
	Triangle tri;
	float lambda, lowest_lambda = 1.0f;
	//obtengo la posicion matricial del primer triangulo del quad de vertices en el que estan ambos extremos del segmento 
	int trianglePx = ((int)P.x)*2, trianglePz = (int)P.z;
	int	triangleQx = ((int)Q.x)*2, triangleQz = (int)Q.z;

	//considero los fuera de rango
	if( (trianglePx < 0 && triangleQx < 0) || (trianglePx > (TERRAIN_SIZE-2)*2 && triangleQx > (TERRAIN_SIZE-2)*2) ) return lowest_lambda;
	if( (trianglePz < 0 && triangleQz < 0) || (trianglePz > (TERRAIN_SIZE-2)   && triangleQz > (TERRAIN_SIZE-2)  ) ) return lowest_lambda;
	
	if(trianglePx < 0) trianglePx = 0;
	else if(trianglePx > (TERRAIN_SIZE-2)*2) trianglePx = (TERRAIN_SIZE-2)*2;
	if(trianglePz < 0) trianglePz = 0;
	else if(trianglePz > TERRAIN_SIZE-2) trianglePz = TERRAIN_SIZE-2;

	if(triangleQx < 0) triangleQx = 0;
	else if(triangleQx > (TERRAIN_SIZE-2)*2) triangleQx = (TERRAIN_SIZE-2)*2;
	if(triangleQz < 0) triangleQz = 0;
	else if(triangleQz > TERRAIN_SIZE-2) triangleQz = TERRAIN_SIZE-2;

	//obtengo la lamba de posibles intersecciones
	if(trianglePx == triangleQx)
	{
		if(trianglePz > triangleQz) std::swap(trianglePz,triangleQz);
		for(int j = trianglePz; j <= triangleQz; j++)
		{
			tri = triangles[j*(TERRAIN_SIZE-1)*2 + trianglePx];
			if(IsColliding(P,Q,tri,lambda) && lambda < lowest_lambda) lowest_lambda = lambda;
			tri = triangles[j*(TERRAIN_SIZE-1)*2 + trianglePx+1];
			if(IsColliding(P,Q,tri,lambda) && lambda < lowest_lambda) lowest_lambda = lambda;
		}
		return lowest_lambda;
	}
	if(trianglePz == triangleQz)
	{
		if(trianglePx > triangleQx) std::swap(trianglePx,triangleQx);
		for(int i = trianglePx; i <= triangleQx+1; i++)
		{
			tri = triangles[trianglePz*(TERRAIN_SIZE-1)*2 + i];
			if(IsColliding(P,Q,tri,lambda) && lambda < lowest_lambda) lowest_lambda = lambda;
		}
		return lowest_lambda;
	}

	if(trianglePx > triangleQx) std::swap(trianglePx,triangleQx);
	if(trianglePz > triangleQz) std::swap(trianglePz,triangleQz);
	for(int i = trianglePx; i <= triangleQx+1; i++)
	{
		for(int j = trianglePz; j <= triangleQz; j++)
		{
			tri = triangles[j*(TERRAIN_SIZE-1)*2 + i];
			if(IsColliding(P,Q,tri,lambda) && lambda < lowest_lambda) lowest_lambda = lambda;
		}
	}
	
	return lowest_lambda;
}