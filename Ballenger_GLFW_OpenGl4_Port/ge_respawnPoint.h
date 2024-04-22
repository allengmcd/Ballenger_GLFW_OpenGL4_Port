#pragma once

#include "Globals.h"
#include "ge_shader.h"
#include "ge_camera.h"
#include "ge_data.h"

#define CIRCLE_RADIUS 2.0f
#define AURA_HEIGHT 3.0f
#define HEIGHT_OFFSET 0.05f

class RespawnPoint
{
public:
	RespawnPoint();
	~RespawnPoint();
	void  Load();
	void  Draw(int tex_id, bool activated, Shader *shader, Camera *camera);
	void  SetPos(float posx, float posy, float posz);
	float GetX();
    float GetY();
    float GetZ();

private:
	float x,y,z;
    unsigned int respawnVBO, respawnVAO, respawnEBO;

    GLfloat respawnBuffer[(3+2)*4];
	GLuint respawnIndices[6];//[6];
};