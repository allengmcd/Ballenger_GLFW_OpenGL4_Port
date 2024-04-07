#include "ge_model.h" 

Model::Model(){}
Model::~Model(){}

int Model::GetDisplayList(char* path, unsigned int vertices_key)
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
				if(err == 1) 
				{
					err = fscanf(fd,"%c",&c); //espacio o salto de linea
					err = 1;
					continue;
				}
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

	int modeBufferSize = 0;

	for(unsigned int i=0; i<faces.size(); i++)
	{
		if(faces[i].size() == 3)
		{
			modeBufferSize += 8*3;
		}
		else
		{
			modeBufferSize += 8*6;
		}
	}

	GLfloat *modelBuffer = (GLfloat*)malloc(sizeof(GLfloat)*modeBufferSize);
	
	unsigned int bufferIndex = 0;
	unsigned int counter = 0;
	
	for(unsigned int i=0; i<faces.size(); i++)
	{
		if(faces[i].size() == 3)
		{
			modelBuffer[bufferIndex++] = vertexs[faces[i][0][0]-1].x;
			modelBuffer[bufferIndex++] = vertexs[faces[i][0][0]-1].y;
			modelBuffer[bufferIndex++] = vertexs[faces[i][0][0]-1].z;
			modelBuffer[bufferIndex++] = normals[faces[i][0][2]-1].x;
			modelBuffer[bufferIndex++] = normals[faces[i][0][2]-1].y;
			modelBuffer[bufferIndex++] = normals[faces[i][0][2]-1].z;
			modelBuffer[bufferIndex++] = texcoords[faces[i][0][1]-1].first;
			modelBuffer[bufferIndex++] = texcoords[faces[i][0][1]-1].second;

			modelBuffer[bufferIndex++] = vertexs[faces[i][1][0]-1].x;
			modelBuffer[bufferIndex++] = vertexs[faces[i][1][0]-1].y;
			modelBuffer[bufferIndex++] = vertexs[faces[i][1][0]-1].z;
			modelBuffer[bufferIndex++] = normals[faces[i][1][2]-1].x;
			modelBuffer[bufferIndex++] = normals[faces[i][1][2]-1].y;
			modelBuffer[bufferIndex++] = normals[faces[i][1][2]-1].z;
			modelBuffer[bufferIndex++] = texcoords[faces[i][1][1]-1].first;
			modelBuffer[bufferIndex++] = texcoords[faces[i][1][1]-1].second;

			modelBuffer[bufferIndex++] = vertexs[faces[i][2][0]-1].x;
			modelBuffer[bufferIndex++] = vertexs[faces[i][2][0]-1].y;
			modelBuffer[bufferIndex++] = vertexs[faces[i][2][0]-1].z;
			modelBuffer[bufferIndex++] = normals[faces[i][2][2]-1].x;
			modelBuffer[bufferIndex++] = normals[faces[i][2][2]-1].y;
			modelBuffer[bufferIndex++] = normals[faces[i][2][2]-1].z;
			modelBuffer[bufferIndex++] = texcoords[faces[i][2][1]-1].first;
			modelBuffer[bufferIndex++] = texcoords[faces[i][2][1]-1].second;
			counter+=3;
			// std::cout << "bufferIndex: " << bufferIndex << std::endl;
		}
		else
		{
			modelBuffer[bufferIndex++] = vertexs[faces[i][0][0]-1].x;
			modelBuffer[bufferIndex++] = vertexs[faces[i][0][0]-1].y;
			modelBuffer[bufferIndex++] = vertexs[faces[i][0][0]-1].z;
			modelBuffer[bufferIndex++] = normals[faces[i][0][2]-1].x;
			modelBuffer[bufferIndex++] = normals[faces[i][0][2]-1].y;
			modelBuffer[bufferIndex++] = normals[faces[i][0][2]-1].z;
			modelBuffer[bufferIndex++] = texcoords[faces[i][0][1]-1].first;
			modelBuffer[bufferIndex++] = texcoords[faces[i][0][1]-1].second;

			modelBuffer[bufferIndex++] = vertexs[faces[i][1][0]-1].x;
			modelBuffer[bufferIndex++] = vertexs[faces[i][1][0]-1].y;
			modelBuffer[bufferIndex++] = vertexs[faces[i][1][0]-1].z;
			modelBuffer[bufferIndex++] = normals[faces[i][1][2]-1].x;
			modelBuffer[bufferIndex++] = normals[faces[i][1][2]-1].y;
			modelBuffer[bufferIndex++] = normals[faces[i][1][2]-1].z;
			modelBuffer[bufferIndex++] = texcoords[faces[i][1][1]-1].first;
			modelBuffer[bufferIndex++] = texcoords[faces[i][1][1]-1].second;

			modelBuffer[bufferIndex++] = vertexs[faces[i][2][0]-1].x;
			modelBuffer[bufferIndex++] = vertexs[faces[i][2][0]-1].y;
			modelBuffer[bufferIndex++] = vertexs[faces[i][2][0]-1].z;
			modelBuffer[bufferIndex++] = normals[faces[i][2][2]-1].x;
			modelBuffer[bufferIndex++] = normals[faces[i][2][2]-1].y;
			modelBuffer[bufferIndex++] = normals[faces[i][2][2]-1].z;
			modelBuffer[bufferIndex++] = texcoords[faces[i][2][1]-1].first;
			modelBuffer[bufferIndex++] = texcoords[faces[i][2][1]-1].second;


			modelBuffer[bufferIndex++] = vertexs[faces[i][0][0]-1].x;
			modelBuffer[bufferIndex++] = vertexs[faces[i][0][0]-1].y;
			modelBuffer[bufferIndex++] = vertexs[faces[i][0][0]-1].z;
			modelBuffer[bufferIndex++] = normals[faces[i][0][2]-1].x;
			modelBuffer[bufferIndex++] = normals[faces[i][0][2]-1].y;
			modelBuffer[bufferIndex++] = normals[faces[i][0][2]-1].z;
			modelBuffer[bufferIndex++] = texcoords[faces[i][0][1]-1].first;
			modelBuffer[bufferIndex++] = texcoords[faces[i][0][1]-1].second;

			modelBuffer[bufferIndex++] = vertexs[faces[i][2][0]-1].x;
			modelBuffer[bufferIndex++] = vertexs[faces[i][2][0]-1].y;
			modelBuffer[bufferIndex++] = vertexs[faces[i][2][0]-1].z;
			modelBuffer[bufferIndex++] = normals[faces[i][2][2]-1].x;
			modelBuffer[bufferIndex++] = normals[faces[i][2][2]-1].y;
			modelBuffer[bufferIndex++] = normals[faces[i][2][2]-1].z;
			modelBuffer[bufferIndex++] = texcoords[faces[i][2][1]-1].first;
			modelBuffer[bufferIndex++] = texcoords[faces[i][2][1]-1].second;

			modelBuffer[bufferIndex++] = vertexs[faces[i][3][0]-1].x;
			modelBuffer[bufferIndex++] = vertexs[faces[i][3][0]-1].y;
			modelBuffer[bufferIndex++] = vertexs[faces[i][3][0]-1].z;
			modelBuffer[bufferIndex++] = normals[faces[i][3][2]-1].x;
			modelBuffer[bufferIndex++] = normals[faces[i][3][2]-1].y;
			modelBuffer[bufferIndex++] = normals[faces[i][3][2]-1].z;
			modelBuffer[bufferIndex++] = texcoords[faces[i][3][1]-1].first;
			modelBuffer[bufferIndex++] = texcoords[faces[i][3][1]-1].second;

			//std::cout << "bufferIndex: " << bufferIndex << std::endl;
			counter+=6;
		}
	}

	modelsVertices[vertices_key] = counter;



    unsigned int modelVBO, modelVAO, modelEBO;

	glGenVertexArrays(1, &playerVAO);
    glGenBuffers(1, &modelVBO);
    glGenBuffers(1, &modelEBO);

    glBindVertexArray(playerVAO);

    glBindBuffer(GL_ARRAY_BUFFER, modelVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*modeBufferSize, modelBuffer, GL_STATIC_DRAW);

    //glBindVertexArray(modelVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	free(modelBuffer);

	return playerVAO;
}



void Model::Load(Shader *Shader, Data *Data)
{
	char modelKey[] = "Models/key.obj\0";
	char modelPortal[] = "Models/portal.obj\0";
	char modelColumn[] = "Models/column.obj\0";

	models[MODEL_KEY] = GetDisplayList(modelKey, MODEL_KEY);
	models[MODEL_PORTAL] = GetDisplayList(modelPortal, MODEL_PORTAL);
	models[MODEL_COLUMN] = GetDisplayList(modelColumn, MODEL_COLUMN);
}


void Model::Draw(int model_id)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_PROGRAM_POINT_SIZE);
	glBindVertexArray(models[model_id]);

	glDrawArrays(GL_TRIANGLES, 0, modelsVertices[model_id]);
	//glDrawArrays(GL_POINTS, 0, super);

    //glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}