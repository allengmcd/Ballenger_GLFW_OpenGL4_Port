#include "ge_data.h"

Data::Data(void) {}
Data::~Data(void){}

int Data::GetID(int img)
{
	return textures[img].GetID();
}

void Data::GetSize(int img, int *w, int *h)
{
	textures[img].GetSize(w,h);
}

bool Data::LoadImage(int img, const char *filename, int type)
{
	int res;

	res = textures[img].Load(filename,type);
	if(!res)
	{
		std::cout << "Failed to load image: " << filename << std::endl;
		return false;
	} 

	return true;
}

bool Data::Load(LevelConfig levelConfig)
{
	int res;

	const char* grass = levelConfig.CurrentLevel.get_data().get_terrain().get_horizontal_texture().c_str();
	const char* rock = levelConfig.CurrentLevel.get_data().get_terrain().get_vertical_texture().c_str();
	char lava[] = "Textures/lava.png\0";
	char skybox[] = "Textures/skybox.png\0";
	char player[] = "Textures/player.png\0";
	char playerNmap[] = "Textures/playerNmap.png\0";
	char circle_on[] = "Textures/circle_on.png\0";
	char circle_off[] = "Textures/circle_off.png\0";
	char vortex[] = "Textures/vortex.png\0";
	char key[] = "Textures/key.png\0";
	char keyNmap[] = "Textures/keyNmap.png\0";
	char portal[] = "Textures/portal.png\0";
	char portalNmap[] = "Textures/portalNmap.png\0";
	char column[] = "Textures/column.png\0";
	char columnNmap[] = "Textures/columnNmap.png\0";
	char skybox_right[] = "Textures/skybox/right.jpg\0";
	char skybox_left[] = "Textures/skybox/left.jpg\0";
	char skybox_top[] = "Textures/skybox/top.jpg\0";
	char skybox_bottom[] = "Textures/skybox/bottom.jpg\0";
	char skybox_front[] = "Textures/skybox/front.jpg\0";
	char skybox_back[] = "Textures/skybox/back.jpg\0";

	res = LoadImage(IMG_GRASS,grass,GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_ROCK,rock,GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_LAVA,lava,GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_SKYBOX,skybox,GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_PLAYER,player,GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_PLAYER_NMAP,playerNmap,GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_CIRCLE_ON,circle_on);
	if(!res) return false;
	res = LoadImage(IMG_CIRCLE_OFF,circle_off,GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_VORTEX,vortex,GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_KEY,key,GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_KEY_NMAP,keyNmap,GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_PORTAL,portal,GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_PORTAL_NMAP,portalNmap,GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_COLUMN,column,GL_RGBA);
	if(!res) return false;
	res = LoadImage(IMG_COLUMN_NMAP,columnNmap,GL_RGBA);
	if(!res) return false;

	return true;
}