#include "ge_respawnPoint.h"

RespawnPoint::RespawnPoint(){}
RespawnPoint::~RespawnPoint(){}


void RespawnPoint::Load()
{
    respawnBuffer[0] = 0.0f;
    respawnBuffer[1] = 1.0f;
    respawnBuffer[2] = CIRCLE_RADIUS;
    respawnBuffer[3] = 0.0f;
    respawnBuffer[4] = -CIRCLE_RADIUS;

    respawnBuffer[5] = 1.0f;
    respawnBuffer[6] = 1.0f;
    respawnBuffer[7] = -CIRCLE_RADIUS;
    respawnBuffer[8] = 0.0f;
    respawnBuffer[9] = -CIRCLE_RADIUS;

    respawnBuffer[10] = 1.0f;
    respawnBuffer[11] = 0.0f;
    respawnBuffer[12] = -CIRCLE_RADIUS;
    respawnBuffer[13] = 0.0f;
    respawnBuffer[14] = CIRCLE_RADIUS;

    respawnBuffer[15] = 0.0f;
    respawnBuffer[16] = 0.0f;
    respawnBuffer[17] = CIRCLE_RADIUS;
    respawnBuffer[18] = 0.0f;
    respawnBuffer[19] = CIRCLE_RADIUS;



    respawnIndices[0] = 0;
    respawnIndices[1] = 1;
    respawnIndices[2] = 3;
    respawnIndices[3] = 1;
    respawnIndices[4] = 2;
    respawnIndices[5] = 3;


    glGenVertexArrays(1, &respawnVAO);
    glGenBuffers(1, &respawnVBO);
    glGenBuffers(1, &respawnEBO);

    glBindVertexArray(respawnVAO);

    glBindBuffer(GL_ARRAY_BUFFER, respawnVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(respawnBuffer), respawnBuffer, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, respawnEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(respawnIndices), respawnIndices, GL_STATIC_DRAW);

    // texture attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // position attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void RespawnPoint::Draw(int tex_id, bool activated, Shader *shader, Camera *camera)
{
	char texture1_name[] = "texture1\0";

    glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view =  camera->GetViewMatrix(); // remove translation from the view matrix
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)camera->SCR_WIDTH/(float)camera->SCR_HEIGHT, 0.1f, 1000.0f);

    model = glm::translate(model, glm::vec3(x,y+HEIGHT_OFFSET,z));


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex_id);

    shader->Activate(PROGRAM_RESPAWNPOINT);
    shader->setInt(texture1_name, 0);
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);

    glBindVertexArray(respawnVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawArrays(GL_QUADS, 0, 4);

    glBindVertexArray(0);
}

void RespawnPoint::SetPos(float posx, float posy, float posz)
{
	x = posx;
	y = posy;
	z = posz;
}
float RespawnPoint::GetX()
{
    return x;
}
float RespawnPoint::GetY()
{
    return y;
}
float RespawnPoint::GetZ()
{
    return z;
}