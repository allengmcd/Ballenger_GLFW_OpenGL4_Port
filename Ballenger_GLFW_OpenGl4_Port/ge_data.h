#pragma once

#include "ge_texture.h"
#include "ge_levelConfig.h"

//Image array size
#define NUM_TEX		 15

//Image identifiers
enum {
	IMG_GRASS,
	IMG_ROCK,
	IMG_LAVA,
	IMG_SKYBOX,
	IMG_PLAYER,
	IMG_PLAYER_NMAP,
	IMG_CIRCLE_ON,
	IMG_CIRCLE_OFF,
	IMG_VORTEX,
	IMG_KEY,
	IMG_KEY_NMAP,
	IMG_PORTAL,
	IMG_PORTAL_NMAP,
	IMG_COLUMN,
	IMG_COLUMN_NMAP,
};

class Data
{
public:
	Data(void);
	~Data(void);

	int  GetID(int img);
	void GetSize(int img, int *w, int *h);
	bool Load(LevelFile::Stage currentStage);

private:
	Texture textures[NUM_TEX];
	bool LoadImage(int img,const char *filename,int type = GL_RGBA);
};
