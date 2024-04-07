#pragma once

#include "Globals.h"
#include "ge_camera.h"
#include "ge_terrain.h"
#include "ge_lava.h"

class PlayerCamera
{
public:
	PlayerCamera();
	~PlayerCamera();

	void Update(Camera *camera,Terrain *terrain,Lava *lava,float player_x,float player_y,float player_z);

private:
};