#include "ge_model.h"

Model::Model(){}
Model::~Model(){}

int Model::GetDisplayList(char* path)
{
	struct Coord { float x,y,z; };

	std::vector<Coord> vertexs;
	std::vector< std::pair<float,float> > texcoords;
	std::vector<Coord> normals; //per vertex
	std::vector< std::vector< std::vector<int> > > faces;
	
	int err;
	char c;
	FILE *fd = fopen(path, "r");

	do {

		err = fscanf(fd,"%c",&c);

		if(c =='v')
		{
			Coord aux;
			if(err == 1) err = fscanf(fd,"%c",&c); //espacio
			if(err == 1) err = fscanf(fd,"%f",&aux.x);
			if(err == 1) err = fscanf(fd,"%c",&c); //espacio
			if(err == 1) err = fscanf(fd,"%f",&aux.y);
			if(err == 1) err = fscanf(fd,"%c",&c); //espacio
			if(err == 1) err = fscanf(fd,"%f",&aux.z);

			vertexs.push_back(aux);
			if(err == 1) err = fscanf(fd,"%c",&c); //salto de linea
		}
		if(c =='t')
		{
			std::pair<float,float> st;
			if(err == 1) err = fscanf(fd,"%c",&c); //espacio
			if(err == 1) err = fscanf(fd,"%f",&st.first);
			if(err == 1) err = fscanf(fd,"%c",&c); //espacio
			if(err == 1) err = fscanf(fd,"%f",&st.second);

			texcoords.push_back(st);
			if(err == 1) err = fscanf(fd,"%c",&c); //salto de linea
		}
		if(c =='n')
		{
			Coord aux;
			if(err == 1) err = fscanf(fd,"%c",&c); //espacio
			if(err == 1) err = fscanf(fd,"%f",&aux.x);
			if(err == 1) err = fscanf(fd,"%c",&c); //espacio
			if(err == 1) err = fscanf(fd,"%f",&aux.y);
			if(err == 1) err = fscanf(fd,"%c",&c); //espacio
			if(err == 1) err = fscanf(fd,"%f",&aux.z);
			
			normals.push_back(aux);
			if(err == 1) err = fscanf(fd,"%c",&c); //salto de linea
		}
		if(c =='f')
		{
			std::vector< std::vector<int> > points;
			std::vector<int> point(3);
			
			if(err == 1) err = fscanf(fd,"%c",&c); //espacio
			
			do {
				if(err == 1) err = fscanf(fd,"%d",&point[0]);
				if(err == 1) err = fscanf(fd,"%c",&c); //separador
				if(err == 1) err = fscanf(fd,"%d",&point[1]);
				if(err == 1) err = fscanf(fd,"%c",&c); //separador
				if(err == 1) err = fscanf(fd,"%d",&point[2]);

				points.push_back(point);
				if(err == 1) err = fscanf(fd,"%c",&c); //espacio o salto de linea
			} while(c ==' ');

			faces.push_back(points);
		}

	} while(!feof(fd));
	
	fclose(fd);


	if(err != 1)
	{
		std::cout << "fscanf error loading model..." << std::endl;
		return -1;
	}
	
	int dl = glGenLists(1);
	glNewList(dl,GL_COMPILE);
	
	for(unsigned int i=0; i<faces.size(); i++)
	{
		if(faces[i].size() == 3)
		{
			glBegin(GL_TRIANGLES);
				glTexCoord2f(texcoords[faces[i][0][1]-1].first, texcoords[faces[i][0][1]-1].second);
				glNormal3f(normals[faces[i][0][2]-1].x, normals[faces[i][0][2]-1].y, normals[faces[i][0][2]-1].z);
				glVertex3f(vertexs[faces[i][0][0]-1].x, vertexs[faces[i][0][0]-1].y, vertexs[faces[i][0][0]-1].z);

				glTexCoord2f(texcoords[faces[i][1][1]-1].first, texcoords[faces[i][1][1]-1].second);
				glNormal3f(normals[faces[i][1][2]-1].x, normals[faces[i][1][2]-1].y, normals[faces[i][1][2]-1].z);
				glVertex3f(vertexs[faces[i][1][0]-1].x, vertexs[faces[i][1][0]-1].y, vertexs[faces[i][1][0]-1].z);

				glTexCoord2f(texcoords[faces[i][2][1]-1].first, texcoords[faces[i][2][1]-1].second);
				glNormal3f(normals[faces[i][2][2]-1].x, normals[faces[i][2][2]-1].y, normals[faces[i][2][2]-1].z);
				glVertex3f(vertexs[faces[i][2][0]-1].x, vertexs[faces[i][2][0]-1].y, vertexs[faces[i][2][0]-1].z);
			glEnd();
		}
		else
		{
			glBegin(GL_QUADS);
				glTexCoord2f(texcoords[faces[i][0][1]-1].first, texcoords[faces[i][0][1]-1].second);
				glNormal3f(normals[faces[i][0][2]-1].x, normals[faces[i][0][2]-1].y, normals[faces[i][0][2]-1].z);
				glVertex3f(vertexs[faces[i][0][0]-1].x, vertexs[faces[i][0][0]-1].y, vertexs[faces[i][0][0]-1].z);

				glTexCoord2f(texcoords[faces[i][1][1]-1].first, texcoords[faces[i][1][1]-1].second);
				glNormal3f(normals[faces[i][1][2]-1].x, normals[faces[i][1][2]-1].y, normals[faces[i][1][2]-1].z);
				glVertex3f(vertexs[faces[i][1][0]-1].x, vertexs[faces[i][1][0]-1].y, vertexs[faces[i][1][0]-1].z);

				glTexCoord2f(texcoords[faces[i][2][1]-1].first, texcoords[faces[i][2][1]-1].second);
				glNormal3f(normals[faces[i][2][2]-1].x, normals[faces[i][2][2]-1].y, normals[faces[i][2][2]-1].z);
				glVertex3f(vertexs[faces[i][2][0]-1].x, vertexs[faces[i][2][0]-1].y, vertexs[faces[i][2][0]-1].z);

				glTexCoord2f(texcoords[faces[i][3][1]-1].first, texcoords[faces[i][3][1]-1].second);
				glNormal3f(normals[faces[i][3][2]-1].x, normals[faces[i][3][2]-1].y, normals[faces[i][3][2]-1].z);
				glVertex3f(vertexs[faces[i][3][0]-1].x, vertexs[faces[i][3][0]-1].y, vertexs[faces[i][3][0]-1].z);
			glEnd();
		}
	}
	
	glEndList();
	
	return dl;
}



void Model::Load()
{
	//models[MODEL_KEY] = GetDisplayList("Models/key.obj");
	//models[MODEL_PORTAL] = GetDisplayList("Models/portal.obj");
	//models[MODEL_COLUMN] = GetDisplayList("Models/column.obj");
}

void Model::Draw(int model_id)
{
	glCallList(models[model_id]);
}