#include "ge_energyBeacon.h"

EnergyBeacon::EnergyBeacon()
{
}
EnergyBeacon::~EnergyBeacon(){}


void EnergyBeacon::Load(unsigned int sectorCount, unsigned int radius, unsigned int height)
{
	// std::vector<glm::vec3> positions;
	// std::vector<glm::vec2> uv;
	// std::vector<glm::vec3> normals;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
	std::vector<unsigned int> indices;


    float sectorStep = 2 * PI / sectorCount;
    float sectorAngle;  // radian

    std::vector<float> unitVertices;
    for(int i = 0; i <= sectorCount; ++i)
    {
        sectorAngle = i * sectorStep;
        unitVertices.push_back(cos(sectorAngle)); // x
        unitVertices.push_back(sin(sectorAngle)); // y
        unitVertices.push_back(0);                // z
    }

// put side vertices to arrays
    for(int i = 0; i < 2; ++i)
    {
        float h = -height / 2.0f + i * height;           // z value; -h/2 to h/2
        float t = 1.0f - i;                              // vertical tex coord; 1 to 0

        for(int j = 0, k = 0; j <= sectorCount; ++j, k += 3)
        {
            float ux = unitVertices[k];
            float uy = unitVertices[k+1];
            float uz = unitVertices[k+2];
            // position vector
            vertices.push_back(glm::vec3(ux * radius, uy * radius, h)); // vx, vy, vz
            // normal vector
            normals.push_back(glm::vec3(ux, uy, uz)); // nx, ny, nz
            // texture coordinate
            texCoords.push_back(glm::vec2((float)j / sectorCount, t)); // s, t
        }
    }

    // the starting index for the base/top surface
    //NOTE: it is used for generating indices later
    int baseCenterIndex = (int)vertices.size() / 3;
    int topCenterIndex = baseCenterIndex + sectorCount + 1; // include center vertex

    // put base and top vertices to arrays
    for(int i = 0; i < 2; ++i)
    {
        float h = -height / 2.0f + i * height;           // z value; -h/2 to h/2
        float nz = -1 + i * 2;                           // z value of normal; -1 to 1

        // center point
        vertices.push_back(glm::vec3(0,0,h));
        normals.push_back(glm::vec3(0,0,nz));
        texCoords.push_back(glm::vec2(0.5f,0.5f));

        for(int j = 0, k = 0; j < sectorCount; ++j, k += 3)
        {
            float ux = unitVertices[k];
            float uy = unitVertices[k+1];
            // position vector
            vertices.push_back(glm::vec3(ux * radius, uy * radius, h)); // vx, vy, vz
            // normal vector
            normals.push_back(glm::vec3(0, 0, nz)); // nx, ny, nz
            // texture coordinate
            texCoords.push_back(glm::vec2(-ux * 0.5f + 0.5f, -uy * 0.5f + 0.5f)); // s, t
        }
    }

	std::vector<float> data;
	for (unsigned int i = 0; i < vertices.size(); ++i)
	{
		data.push_back(vertices[i].x);
		data.push_back(vertices[i].y);
		data.push_back(vertices[i].z);
		if (normals.size() > 0)
		{
			data.push_back(normals[i].x);
			data.push_back(normals[i].y);
			data.push_back(normals[i].z);
		}
		if (texCoords.size() > 0)
		{
			data.push_back(texCoords[i].x);
			data.push_back(texCoords[i].y);
		}
	}


    // generate CCW index list of cylinder triangles
    int k1 = 0;                         // 1st vertex index at base
    int k2 = sectorCount + 1;           // 1st vertex index at top

    // indices for the side surface
    for(int i = 0; i < sectorCount; ++i, ++k1, ++k2)
    {
        // 2 triangles per sector
        // k1 => k1+1 => k2
        indices.push_back(k1);
        indices.push_back(k1 + 1);
        indices.push_back(k2);

        // k2 => k1+1 => k2+1
        indices.push_back(k2);
        indices.push_back(k1 + 1);
        indices.push_back(k2 + 1);
    }

    // indices for the base surface
    //NOTE: baseCenterIndex and topCenterIndices are pre-computed during vertex generation
    //      please see the previous code snippet
    for(int i = 0, k = baseCenterIndex + 1; i < sectorCount; ++i, ++k)
    {
        if(i < sectorCount - 1)
        {
            indices.push_back(baseCenterIndex);
            indices.push_back(k + 1);
            indices.push_back(k);
        }
        else // last triangle
        {
            indices.push_back(baseCenterIndex);
            indices.push_back(baseCenterIndex + 1);
            indices.push_back(k);
        }
    }

    // indices for the top surface
    for(int i = 0, k = topCenterIndex + 1; i < sectorCount; ++i, ++k)
    {
        if(i < sectorCount - 1)
        {
            indices.push_back(topCenterIndex);
            indices.push_back(k);
            indices.push_back(k + 1);
        }
        else // last triangle
        {
            indices.push_back(topCenterIndex);
            indices.push_back(k);
            indices.push_back(topCenterIndex + 1);
        }
    }

    // int counter = 0;
    for(int i = 0; i < data.size(); i+=8)
    {
        data[i+2] = i;
        //std::cout << data[i+0] << " : " << data[i+1] <<  " : " << data[i+2] <<std::endl;
        // std::cout << data[i+3] << " : " << data[i+4] <<  " : " << data[i+5] <<std::endl;
        // std::cout << data[i+6] << " : " << data[i+7] <<  std::endl;
        //std::cout << "" <<  std::endl;
        //counter++;
    }

    float vertices2[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices2[] = {  
        0, 1, 2, 1, 2, 3, 2, 3, 4, 3, 4, 5, 4, 5, 6, 6, 7, 8, 7, 8, 9, 8, 9, 10, 9, 10, 11, 10, 11, 12, 11, 12, 13
    };

    // for(int i = 3; i < 28; i++)
    // {
    //     //data[i] = vertices2[i];
    //     indices2[i+0] = i-2;
    //     indices2[i+1] = i-1;
    //     indices2[i+2] = i;
    // }
    // for(int i = 0; i < 32; i++)
    // {
    //     std::cout << indices2[i] << std::endl;
    // }


    indexCount = data.size()/8;

	unsigned int vbo, ebo, vao;
    glGenVertexArrays(1, &beaconVAO);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

    glBindVertexArray(beaconVAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(float), &data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &indices2[0], GL_STATIC_DRAW);
	unsigned int stride = (3 + 2 + 3) * sizeof(float);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));

    //beaconVAO = vao;
}

int counter1 = 0;
int counter2 = 0;
void EnergyBeacon::Draw(Data *data, Camera *camera, Shader *shader)
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view =  camera->GetViewMatrix(); // remove translation from the view matrix
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)camera->SCR_WIDTH/(float)camera->SCR_HEIGHT, 0.1f, 1000.0f);


    model = glm::translate(model, glm::vec3(GetX(), GetY(), GetZ()));
	//model = glm::rotate(model, -GetPitch()/100, glm::vec3(-cos(GetYaw()*(PI/180))/100,0.0,sin(GetYaw()*(PI/180))/100));


	shader->Activate(PROGRAM_ENERGYBEACON);
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

    glBindVertexArray(beaconVAO);

    counter1++;
    if(counter1 >= 50)
    {
        if(counter2 >=20) counter2 = 0;
        counter2++;
        counter1 = 0;
    }
    glDrawElements(GL_TRIANGLES, counter2, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLE_STRIP, 24, 0);
   	// glBindVertexArray(beaconVAO);
    // // glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
    // glDrawElements(GL_TRIANGLE_STRIP, 21, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

float EnergyBeacon::GetX()
{
	return x;
}
float EnergyBeacon::GetY()
{
	return y;
}
float EnergyBeacon::GetZ()
{
	return z;
}
float EnergyBeacon::GetYaw()
{
	return yaw;
}
void EnergyBeacon::SetEnergyBeacon(float posx, float posy, float posz, float ang)
{
	x = posx;
	y = posy;
	z = posz;
	yaw = ang;
}