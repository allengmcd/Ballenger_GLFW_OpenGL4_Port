#pragma once

#include "ge_scene.h"
#include "ge_shader.h"
#include "ge_camera.h"
#include "ge_skybox.h"
#include "ge_terrain.h"
#include "ge_model.h"
#include "ge_key.h"
#include "ge_player.h"


#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

#define FRAMERATE 60
#define GRAVITY 0.015f

enum{
	STATE_LIVELOSS,
	STATE_RUN,
	STATE_ENDGAME
};

#define TOTAL_LEVELS	  1

//controls
#define P_UP		'w'
#define P_DOWN		's'
#define P_LEFT		'a'
#define P_RIGHT		'd'
#define P_JUMP		' '
#define P_PLUS		'+'
#define P_MINUS		'-'

class Game
{
public:
	Game(void);
	virtual ~Game(void);

	Camera *camera;

    unsigned int skyboxVAO, skyboxVBO;
	unsigned int cubemapTexture;
	
	bool Init(int lvl, GLFWwindow *window);
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	void ReadMouseMotion(int x, int y);
	//Process
	bool Process();
	//Output
	void Reshape(int w, int h);
	void Render();

private:
	unsigned char keys[256];
	bool mouse_left_down,mouse_right_down;
	int level,state,pickedkey_id;
	unsigned int respawn_id;
	bool noclip,portal_activated;
	float time,ang, noclipSpeedF;
	Data data;
	Shader shader;
	Scene scene;
	Terrain terrain;
	Lava lava;
	Model model;
	Player player;
	GLFWwindow *window;

	//void Physics(Bicho &object);
};