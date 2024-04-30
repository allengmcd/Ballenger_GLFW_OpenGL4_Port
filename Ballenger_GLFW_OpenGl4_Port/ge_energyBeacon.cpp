#include "ge_energyBeacon.h"

EnergyBeacon::EnergyBeacon()
{
}
EnergyBeacon::~EnergyBeacon(){}


void EnergyBeacon::Load(unsigned int sectorCount, float radius, float height)
{
    float sectorIncrement = (2*PI)/sectorCount;


    std::vector<glm::vec3> vertices_top;
    std::vector<glm::vec3> vertices_bottom;
    for(int i =0 ; i < sectorCount; i++)
    {
        glm::vec3 vertex;
        vertex.x = radius * cos(i*sectorIncrement);
        vertex.y = 0.0f;
        vertex.z = radius * sin(i*sectorIncrement);

        vertices_top.push_back(vertex);
    }



    for(int i =0 ; i < sectorCount; i++)
    {
        glm::vec3 vertex;
        vertex.x = radius * cos(i*sectorIncrement);
        vertex.y = height;
        vertex.z = radius * sin(i*sectorIncrement);

        vertices_bottom.push_back(vertex);
    }


    std::vector<float> data;
    for(int i = 0; i < vertices_bottom.size() && i < vertices_top.size(); i++)
    {
        data.push_back(vertices_top[i].x);
        data.push_back(vertices_top[i].y);
        data.push_back(vertices_top[i].z);
        data.push_back(0.0f);
        data.push_back(0.0f);
        data.push_back(0.0f);
        data.push_back(0.0f);
        data.push_back(0.0f);
        data.push_back(vertices_bottom[i].x);
        data.push_back(vertices_bottom[i].y);
        data.push_back(vertices_bottom[i].z);
        data.push_back(0.0f);
        data.push_back(0.0f);
        data.push_back(0.0f);
        data.push_back(0.0f);
        data.push_back(0.0f);
    }

    std::vector<unsigned int> indices;
    for(int i =0; i <= (data.size()/8)-2; i+=2)
    {
        int vertex1 = 0;
        int vertex2 = 0;
        int vertex3 = 0;
        int vertex4 = 0;

        if(i < (data.size()/8)-2)
        {
            vertex1 = i;
            vertex2 = i+1;
            vertex3 = i+2;
            vertex4 = i+3;
        }
        else
        {
            vertex1 = i;
            vertex2 = i+1;
            vertex3 = 0;
            vertex4 = 1;	
        }

        
        indices.push_back(vertex1);
        indices.push_back(vertex2);
        indices.push_back(vertex3);
        
        indices.push_back(vertex2);
        indices.push_back(vertex3);
        indices.push_back(vertex4);



        std::cout << "triangle1: " << data[vertex1*8] << " : " << data[vertex2*8] << " : " << data[vertex3*8] << std::endl;
        std::cout << "triangle2: " << data[vertex2*8] << " : " << data[vertex3*8] << " : " << data[vertex4*8] << std::endl;
        std::cout << std::endl;
    }


    indexCount = indices.size();
	unsigned int vbo, ebo, vao;
    glGenVertexArrays(1, &beaconVAO);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

    glBindVertexArray(beaconVAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	unsigned int stride = (3 + 2 + 3) * sizeof(float);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));

    //beaconVAO = vao;
    ang = 0;
}

int counter1 = 0;
int counter2 = 0;
void EnergyBeacon::Draw(Data *data, Camera *camera, Shader *shader, glm::vec4 beaconColor )
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view =  camera->GetViewMatrix(); // remove translation from the view matrix
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)camera->SCR_WIDTH/(float)camera->SCR_HEIGHT, 0.1f, 1000.0f);

    
    model = glm::translate(model, glm::vec3(GetX(), GetY(), GetZ()));
	//model = glm::rotate(model, PI/2, glm::vec3(1.0f,0.0,0.0f));


    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	shader->Activate(PROGRAM_ENERGYBEACON);
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);
	shader->setVec4("bColor", beaconColor);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(beaconVAO);


    // glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_TRIANGLE_STRIP, 0, indexCount);
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