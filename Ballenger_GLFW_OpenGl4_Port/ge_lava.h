#pragma once

#include "Globals.h"
#include "ge_texture.h"
#include "ge_shader.h"
#include "ge_data.h"
#include "ge_camera.h"
#include "ge_image.h"

#define FLOW_SPEED 2.0f
#define LAVA_HEIGHT_MAX 4.0f
#define LAVA_HEIGHT_MIN 1.0f

class Lava
{
public:
	Lava();
	~Lava();
	void Load(float terrain_size, float max_height, float min_height, float flow_speed, Shader *Shader, Data *Data);
	void Draw(Camera *camera);
	float GetHeight();
	float GetHeightMax();
	void Update();

private:
	int id_Lava;
	float height,ang, max_height, min_height, flow_speed;
	bool up;
    GLfloat lavaBuffer[(3+2)*4];
	GLuint lavaIndices[32];//[6];
    unsigned int lavaVBO, lavaVAO, lavaEBO;
	Shader *shader;
	Data *data;


    // load and create a texture 
    // -------------------------
    unsigned int texture1;
};