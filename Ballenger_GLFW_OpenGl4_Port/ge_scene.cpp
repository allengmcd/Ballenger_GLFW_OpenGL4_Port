#include "ge_scene.h"

Scene::Scene(void){}
Scene::~Scene(void){}


void Scene::LoadLevel(LevelConfig levelConfig, Terrain *Terrain, Shader *Shader, Data *Data, Lava *Lava)
{
	int level = atoi(levelConfig.CurrentLevel.get_id().c_str());

	Data->Load(levelConfig);
	Terrain->Load(level, Shader, Data);

	std::cout << "Initializing skybox..." << std::endl;
	skybox.Load(Shader);
	Lava->Load(TERRAIN_SIZE, Shader, Data);
}

void Scene::Draw(Terrain *Terrain, Shader *Shader, Camera *Camera, Data *Data, Lava *Lava)
{
	Terrain->Draw(Camera);
	skybox.Draw(Camera);
	Lava->Draw(Camera);
}