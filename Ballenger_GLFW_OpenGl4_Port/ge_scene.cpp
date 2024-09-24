#include "ge_scene.h"

Scene::Scene(void){}
Scene::~Scene(void){}


void Scene::LoadLevel(LevelFile::Stage currentStage, Terrain *Terrain, Shader *Shader, Data *Data, Lava *Lava)
{
	int level = atoi(currentStage.get_id().c_str());
	float max_height = (float)currentStage.get_data().get_lava().get_top();
	float min_height = (float)currentStage.get_data().get_lava().get_bottom();
	float flow_speed = (float)currentStage.get_data().get_lava().get_interval();

	Data->Load(currentStage);
	Terrain->Load(level, Shader, Data);

	std::cout << "Initializing skybox..." << std::endl;
	skybox.Load(Shader);
	Lava->Load(TERRAIN_SIZE, max_height, min_height, flow_speed, Shader, Data);
}

void Scene::Draw(Terrain *Terrain, Shader *Shader, Camera *Camera, Data *Data, Lava *Lava)
{
	Terrain->Draw(Camera);
	skybox.Draw(Camera);
	Lava->Draw(Camera);
}