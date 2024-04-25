#pragma once

#include "Globals.h"
#include "ge_shader.h"
#include "ge_model.h"
#include "ge_data.h"
#include "ge_energyBeacon.h"

#define LEVITATION_SPEED 2.0f
#define BEACON_MIN_RADIUS 0.75f
#define BEACON_HEIGHT 140.0f

class Key
{
public:
	Key();
	~Key();
	void  DrawLevitating(Camera *camera, Shader *Shader, Model *key_model, Data *Data, glm::vec4 color, float dist);
	void  DrawPicked(float playerx,float playery, float playerz, float camera_yaw, Camera *camera, Shader *shader, Model *key_model, Data *data, glm::vec4 color);
	void  DrawDeployed(float holex,float holey, float holez, float yaw, Camera *camera, Model *key_model, Data *data, Shader *shader, glm::vec4 color);
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

	EnergyBeacon energyBeacon;
};