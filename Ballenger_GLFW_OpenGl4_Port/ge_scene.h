#pragma once


#include "ge_terrain.h"
#include "ge_skybox.h"
#include "ge_shader.h"
#include "ge_data.h"
#include "ge_lava.h"

class Scene
{
public:
	Scene(void);
	virtual ~Scene(void);

	void LoadLevel(LevelFile::Stage currentStage, Terrain *Terrain, Shader *Shader, Data *Data, Lava *Lava);
	void Draw(Terrain *Terrain, Shader *Shader, Camera *Camera, Data *Data, Lava *Lava);

private:
	Skybox skybox;
};
