#include "ge_game.h"
#include<unistd.h> 


unsigned int loadCubemap(std::vector<std::string> faces);

Game::Game(void) 
{
	debug_camera_active = true;
}
Game::~Game(void){}


bool Game::Init(int lvl, GLFWwindow *newWindow)
{
	levelConfig.LoadLevel(1);
	stages = levelConfig.CurrentLevel.get_stages();
	currentStage = 0; // TODO: Make sure that this doesn't crash the program
	window = newWindow;
	activeStage.Init(stages.at(currentStage), newWindow);
	state = STATE_RUN;

	return 1;
}

bool first_round = true;

bool Game::Loop()
{
	bool res=true;

	// Process();
	// Render();

	if(activeStage.state == STATE_RUN)
	{
		res = activeStage.Process();
		if(res) activeStage.Render();
		if(first_round) activeStage.state = STATE_ENDGAME;
	}
	else if(activeStage.state == STATE_LIVELOSS)
	{
		activeStage.Render();
		activeStage.player.SetPos(activeStage.respawn_points[activeStage.respawn_id].GetX(),
			activeStage.respawn_points[activeStage.respawn_id].GetY()+RADIUS,
			activeStage.respawn_points[activeStage.respawn_id].GetZ());
		activeStage.state = STATE_RUN;
	}
	else if(activeStage.state == STATE_ENDGAME)
	{
		res=false;
		currentStage++;
		activeStage.state = STATE_INIT;
	}
	else if(activeStage.state == STATE_INIT)
	{
		Stage *tempStage = new Stage();
		activeStage = *tempStage;
		std::cout << stages.size() << std::endl;
		activeStage.Init(stages.at(currentStage), window);
		activeStage.state = STATE_RUN;
		first_round = false;
	}

	return res;
}


void Game::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	if(key >= 'A' && key <= 'Z') key += 32;
	activeStage.keys[key] = press;
}

void Game::ReadMouseMotion(int x, int y)
{
	//la cantidad desplazada en pixeles
    int dx = x;// - SCREEN_WIDTH/2;
    int dy = -y;// - SCREEN_HEIGHT/2;

    if(dx) {
        activeStage.camera->RotateYaw(CAMERA_SPEED*dx);
		if(activeStage.camera->GetState() != STATE_TPS_FREE) activeStage.camera->SetLastYaw(activeStage.camera->GetYaw());
    }

    if(dy) {
        activeStage.camera->RotatePitch(-CAMERA_SPEED*dy);
    }

}

void Game::ToggleCamera(bool debug_camera_active)
{
	if(debug_camera_active)
	{
		activeStage.camera = activeStage.debug_camera;
	}
	else
	{
		activeStage.camera = activeStage.player_camera;
	}
}