#pragma once

#include "ge_scene.h"
#include "ge_shader.h"
#include "ge_camera.h"
#include "ge_skybox.h"
#include "ge_terrain.h"
#include "ge_model.h"
#include "ge_column.h"
#include "ge_key.h"
#include "ge_player.h"
#include "ge_portal.h"
#include "ge_respawnPoint.h"
#include "ge_playerCamera.h"
#include "ge_levelConfig.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600

#define FRAMERATE 60
#define GRAVITY 0.015f

#define TOTAL_LEVELS	  1


enum{
	STATE_LIVELOSS,
	STATE_RUN,
	STATE_ENDGAME,
	STATE_INIT
};

#define CAMERA_ZFAR   (TERRAIN_SIZE/sin(PI/4))
#define CAMERA_ZNEAR  0.01f
#define CAMERA_MAX_DISTANCE   10.0f
#define CAMERA_SPEED  (PI/180*0.1)
#define CAMERA_SMOOTHING_SPEED  0.01f

//controls
#define P_UP		'w'
#define P_DOWN		's'
#define P_LEFT		'a'
#define P_RIGHT		'd'
#define P_JUMP		' '
#define P_PLUS		'+'
#define P_MINUS		'-'


class Stage
{
public:
	Stage(void);
	virtual ~Stage(void);

	PlayerCamera playerCamera;
	Camera *debug_camera;
	Camera *player_camera;
	Camera *camera;
	Player player;
	std::vector<RespawnPoint> respawn_points;

    unsigned int skyboxVAO, skyboxVBO;
	unsigned int cubemapTexture;
	
	unsigned char keys[256];
	bool mouse_left_down,mouse_right_down;
	int level,state,pickedkey_id;
	unsigned int respawn_id;
	bool noclip,portal_activated;
	bool debug_camera_active;
	float time,ang, noclipSpeedF;
	
	bool Init(LevelFile::Stage currentStage, GLFWwindow *window);
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	void ReadMouseMotion(int x, int y);
	//Process
	bool Process();
	void Physics(Bicho &object);
	//Output
	void Reshape(int w, int h);
	void Render();
	void ToggleCamera(bool debug_camera_active);

private:
	std::vector<Key> target_keys;
	std::vector<Column> columns;
	Portal portal;
	Data data;
	Shader shader;
	Scene scene;
	Terrain terrain;
	Lava lava;
	Model model;
	GLFWwindow *window;
	Key key;
	EnergyBeacon energyBeacon;
	//LevelConfig levelConfig;

	//void Physics(Bicho &object);
};