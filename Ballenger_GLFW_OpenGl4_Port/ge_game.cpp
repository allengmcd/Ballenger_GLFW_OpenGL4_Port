#include "ge_game.h"
#include<unistd.h> 


unsigned int loadCubemap(std::vector<std::string> faces);

Game::Game(void) {}
Game::~Game(void){}


bool Game::Init(int lvl, GLFWwindow *newWindow)
{
	window = newWindow;

	state = STATE_RUN;

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

	// //Sound initialization
	//sound.Load();

	//Texture initialization
	data.Load();

    //Shader initialization
	shader.Load();

	//Model initialization
	model.Load();

	//level initialization(terrain, lava and skybox)
	scene.LoadLevel(1,&terrain,&shader,&data,&lava);

	//Player initialization
	player.Load();
	player.SetPos(TERRAIN_SIZE/2, terrain.GetHeight(TERRAIN_SIZE/2,TERRAIN_SIZE/2)+RADIUS,TERRAIN_SIZE/2);

	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	//sound.Play(SOUND_AMBIENT); //TODO: this causes segfault
	//sound.PlayBounce(.25f); //TODO: So does this

	//return res;
	return 1;
}

bool Game::Loop()
{
	bool res=true;

	Render();

	return res;
}

void Game::Finalize()
{
}


void Game::Render()
{
	// render
	// ------
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(state != STATE_LIVELOSS) lava.Update();

	//skybox.Draw(camera);
	scene.Draw(&terrain,&shader,camera,&data,&lava);

	
	//draw player
	player.Draw(&data,camera,&lava,&shader);

	// if(abs(camera.GetZ()-Portal.GetZ()) < Camera.GetDistance())
	// {
	// 	//draw player
	// 	Player.Draw(&Data,&Camera,&Lava,&Shader);

	// 	//draw portal
	// 	Portal.Draw(&Data,portal_activated,&Shader,&Model);
	// }
	// else
	// {
		//draw portal
		//portal.Draw(&data,portal_activated,&shader,&model);
	
		//draw player
		//player.Draw(&data,camera,&lava,&shader);
	// }


	// //draw keys
	// for(unsigned int i=0; i<target_keys.size(); i++)
	// {
	// 	//color dye
	// 	if(i==0) glColor3f(1.0f,0.0f,0.0f); //rojo
	// 	if(i==1) glColor3f(1.0f,1.0f,0.0f); //amarillo
	// 	if(i==2) glColor3f(0.0f,1.0f,0.0f); //verde
	// 	if(i==3) glColor3f(0.2f,0.2f,1.0f); //azul
	// 	if(i==4) glColor3f(1.0f,0.0f,1.0f); //violeta

	// 	if(i==pickedkey_id) target_keys[i].DrawPicked(Player.GetX(),Player.GetY(),Player.GetZ(),Camera.GetYaw(),&Model,&Data,&Shader);
	// 	else if(target_keys[i].IsDeployed())
	// 	{
	// 		target_keys[i].DrawDeployed(columns[i].GetHoleX(),columns[i].GetHoleY(),columns[i].GetHoleZ(),columns[i].GetYaw(),&Model,&Data,&Shader);
			
	// 		//ray color
	// 		if(i==0) glColor4f(1.0f,0.0f,0.0f,0.4f); //rojo
	// 		if(i==1) glColor4f(1.0f,1.0f,0.0f,0.4f); //amarillo
	// 		if(i==2) glColor4f(0.0f,1.0f,0.0f,0.4f); //verde
	// 		if(i==3) glColor4f(0.2f,0.2f,1.0f,0.4f); //azul
	// 		if(i==4) glColor4f(1.0f,0.0f,1.0f,0.4f); //violeta

	// 		float r = ENERGY_BALL_RADIUS/2.0f; //energy ray radius
	// 		int numrays = 6;
	// 		glDisable(GL_LIGHTING);
	// 		for(int j=0; j<numrays; j++)
	// 		{
	// 			float ang_rad = (ang+j*(360/numrays))*(PI/180);
	// 			glEnable(GL_BLEND);
	// 			glLineWidth(2.0);
	// 			glBegin(GL_LINES);
	// 				glVertex3f(columns[i].GetX()+cos(ang_rad)*r, columns[i].GetY()+COLUMN_HEIGHT+ENERGY_BALL_RADIUS+sin(ang_rad)*r, columns[i].GetZ());
	// 				glVertex3f(Portal.GetReceptorX(i), Portal.GetReceptorY(i), Portal.GetZ());
	// 			glEnd();
	// 			glDisable(GL_BLEND);
	// 		}
	// 		glEnable(GL_LIGHTING);
	// 	}
	// 	else
	// 	{
	// 		float dist = sqrt( (Player.GetX()-target_keys[i].GetX())*(Player.GetX()-target_keys[i].GetX()) + (Player.GetZ()-target_keys[i].GetZ())*(Player.GetZ()-target_keys[i].GetZ()) );
	// 		target_keys[i].DrawLevitating(&Shader,&Model,&Data, dist);
	// 	}

	// 	glColor4f(1,1,1,1);
	// }
	

	glfwSwapBuffers(window);
}
