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

	void Draw(Data *data, Camera *camera, Lava *lava,Shader *shader);
	void SetFade(bool b);
	void Load();
	void RenderSphere();


private:
	bool fade;
    unsigned int playerVBO, playerVAO, playerEBO, indexCount;
};