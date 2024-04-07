#pragma once

#include "Globals.h"
#include "ge_shader.h"
#include "ge_model.h"
#include "ge_data.h"

#define COLUMN_HEIGHT      7.0f
#define ENERGY_BALL_RADIUS 1.0f
#define GATHERNG_AREA_SIDE 4.0f

class Column
{
public:
	Column();
	~Column();
	void Draw(Shader *shader,Model *model,Data *data,Camera *camera,int id);
	void SetColumn(float posx, float posy, float posz, float ang);
	bool InsideGatheringArea(float posx, float posy, float posz);
	float GetX();
	float GetY();
	float GetZ();
	float GetHoleX();
	float GetHoleY();
	float GetHoleZ();
	float GetYaw();

private:
	int id_Column;
	float x,y,z;
	float yaw;
};