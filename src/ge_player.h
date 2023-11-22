#pragma once

#include "ge_bicho.h"
#include "ge_camera.h"

#define PLAYER_SPEED  0.008f
#define PLAYER_JUMP_SPEED  0.4f
#define FRICTION   0.05f
#define ELASTICITY   0.5f //porcentaje de rango [0.0, 1.0]
#define MAX_MOVEMENT 0.4f
#define RADIUS   0.5f

class Player: public Bicho
{
public:
	Player();
	~Player();

	void Draw(Data *Data, Camera *Camera, Lava *Lava,Shader *Shader);
	void SetFade(bool b);

private:
	bool fade;
};