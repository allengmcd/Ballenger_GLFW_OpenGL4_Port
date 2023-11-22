#include "ge_lava.h"

Lava::Lava()
{
	height = (LAVA_HEIGHT_MAX + LAVA_HEIGHT_MIN)/2;
	ang = 0.0f;
	up = true;
}
Lava::~Lava(){}

void Lava::Load(float terrain_size, Shader *Shader, Data *Data)
{
	shader = Shader;
    data = Data;

    lavaBuffer[0] = 0.0f;
    lavaBuffer[1] = 16.0f;
    lavaBuffer[2] = terrain_size;
    lavaBuffer[3] = 0.0f;
    lavaBuffer[4] = 0.0f;

    lavaBuffer[5] = 16.0f;
    lavaBuffer[6] = 16.0f;
    lavaBuffer[7] = 0.0f;
    lavaBuffer[8] = 0.0f;
    lavaBuffer[9] = 0.0f;

    lavaBuffer[10] = 16.0f;
    lavaBuffer[11] = 0.0f;
    lavaBuffer[12] = 0.0f;
    lavaBuffer[13] = 0.0f;
    lavaBuffer[14] = terrain_size;

    lavaBuffer[15] = 0.0f;
    lavaBuffer[16] = 0.0f;
    lavaBuffer[17] = terrain_size;
    lavaBuffer[18] = 0.0f;
    lavaBuffer[19] = terrain_size;



    unsigned int lavaIndices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &lavaVAO);
    glGenBuffers(1, &lavaVBO);
    glGenBuffers(1, &lavaEBO);

    glBindVertexArray(lavaVAO);

    glBindBuffer(GL_ARRAY_BUFFER, lavaVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lavaBuffer), lavaBuffer, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lavaEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lavaIndices), lavaIndices, GL_STATIC_DRAW);

    // texture attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // position attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}


void Lava::Draw(Camera *camera)
{
	char texture1_name[] = "texture1\0";

    glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view =  camera->GetViewMatrix(); // remove translation from the view matrix
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)camera->SCR_WIDTH/(float)camera->SCR_HEIGHT, 0.1f, 1000.0f);
	
    model = glm::translate(model, glm::vec3(0.0f, height, 0.0f));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_LAVA));

    shader->Activate(PROGRAM_LAVAGLOW);
    shader->setInt(texture1_name, 0);
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);


    glBindVertexArray(lavaVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_QUADS, 0, 4);

    glBindVertexArray(0);
}

float Lava::GetHeight()
{
	return height;
}

float Lava::GetHeightMax()
{
	return LAVA_HEIGHT_MAX;
}

void Lava::Update()
{
	if(up)
	{
		ang = fmod(ang+FLOW_SPEED,360);
		height = ((LAVA_HEIGHT_MAX - LAVA_HEIGHT_MIN)/2.0f)*sin(ang*(PI/180)) + (LAVA_HEIGHT_MAX + LAVA_HEIGHT_MIN)/2.0f;
		up = (height < LAVA_HEIGHT_MAX);
	}
	else
	{
		ang = fmod(ang-FLOW_SPEED,360);
		height = ((LAVA_HEIGHT_MAX - LAVA_HEIGHT_MIN)/2.0f)*sin(ang*(PI/180)) + (LAVA_HEIGHT_MAX + LAVA_HEIGHT_MIN)/2.0f;
		up = (height <= LAVA_HEIGHT_MIN);
	}
}