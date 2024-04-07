#pragma once

#include "Globals.h"
#include "ge_shader.h"
#include "ge_model.h"
#include "ge_data.h"

#define LEVITATION_SPEED 2.0f
#define BEACON_MIN_RADIUS 0.75f
#define BEACON_HEIGHT 140.0f

class Key
{
public:
	Key();
	~Key();
	void  DrawLevitating(Camera *camera, Shader *Shader, Model *Model, Data *Data, glm::vec4 color, float dist);
	void  DrawPicked(float playerx,float playery, float playerz, float camera_yaw, Model *Model, Data *Data, Shader *Shader);
	void  DrawDeployed(float holex,float holey, float holez, float yaw, Model *Model, Data *Data, Shader *Shader);
	void  SetPos(float posx, float posy, float posz);
	float GetX();
    float GetY();
    float GetZ();
	void  Deploy();
	bool  IsDeployed();

private:
	float x,y,z; //posicion inicial
	float ang;
	bool deployed;
};