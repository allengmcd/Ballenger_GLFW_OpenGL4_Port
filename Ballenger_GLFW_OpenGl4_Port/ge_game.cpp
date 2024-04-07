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
	model.Load(&shader,&data);
	
	//level initialization(terrain, lava and skybox)
	scene.LoadLevel(1,&terrain,&shader,&data,&lava);

	float test = terrain.GetHeight(345,229);
	test = terrain.GetHeight(883,141);
	test = terrain.GetHeight(268,860);
	test = terrain.GetHeight(780,858);
	test = terrain.GetHeight(265,487);


	// //columns initialization
	Column col;
	col.SetColumn(TERRAIN_SIZE/2+18,terrain.GetHeight(TERRAIN_SIZE/2+18,TERRAIN_SIZE/2+8),TERRAIN_SIZE/2+8,   90);
	columns.push_back(col);
	col.SetColumn(TERRAIN_SIZE/2+14,terrain.GetHeight(TERRAIN_SIZE/2+14,TERRAIN_SIZE/2-8),TERRAIN_SIZE/2-8,   90);
	columns.push_back(col);
	col.SetColumn(TERRAIN_SIZE/2,terrain.GetHeight(TERRAIN_SIZE/2,TERRAIN_SIZE/2-16),TERRAIN_SIZE/2-16,      180);
	columns.push_back(col);
	col.SetColumn(TERRAIN_SIZE/2-14,terrain.GetHeight(TERRAIN_SIZE/2-14,TERRAIN_SIZE/2-8),TERRAIN_SIZE/2-8,  -90);
	columns.push_back(col);
	col.SetColumn(TERRAIN_SIZE/2-18,terrain.GetHeight(TERRAIN_SIZE/2-18,TERRAIN_SIZE/2+8),TERRAIN_SIZE/2+8,  -90);
	columns.push_back(col);


	key.SetPos(883,terrain.GetHeight(883,141),141);
	target_keys.push_back(key);
	key.SetPos(345,terrain.GetHeight(345,229),229);
	target_keys.push_back(key);
	key.SetPos(268,terrain.GetHeight(268,860),860);
	target_keys.push_back(key);
	key.SetPos(780,terrain.GetHeight(780,858),858);
	target_keys.push_back(key);
	key.SetPos(265,terrain.GetHeight(265,487),487);
	target_keys.push_back(key);


	RespawnPoint rp;
	rp.SetPos(TERRAIN_SIZE/2,terrain.GetHeight(TERRAIN_SIZE/2,TERRAIN_SIZE/2),TERRAIN_SIZE/2);
	respawn_points.push_back(rp);
	rp.SetPos(256,terrain.GetHeight(256,160),160);
	respawn_points.push_back(rp);
	rp.SetPos(840,terrain.GetHeight(840,184),184);
	respawn_points.push_back(rp);
	rp.SetPos(552,terrain.GetHeight(552,760),760);
	respawn_points.push_back(rp);
	rp.SetPos(791,terrain.GetHeight(791,850),850);
	respawn_points.push_back(rp);
	rp.SetPos(152,terrain.GetHeight(152,832),832);
	respawn_points.push_back(rp);
	rp.SetPos(448,terrain.GetHeight(448,944),944);
	respawn_points.push_back(rp);
	rp.SetPos(816,terrain.GetHeight(816,816),816);
	respawn_points.push_back(rp);

	//Portal initialization
	portal.SetPos(TERRAIN_SIZE/2,terrain.GetHeight(TERRAIN_SIZE/2,TERRAIN_SIZE/2+32),TERRAIN_SIZE/2+32);

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


	//target_keys[0].DrawLevitating(camera,&shader,&model,&data, 100);
	//draw keys
	glm::vec4 key_color = glm::vec4(0.0f,0.0f,0.0f,0.0f);
	for(unsigned int i=0; i<target_keys.size(); i++)
	{
		if(i==0) key_color = glm::vec4(1.0f,0.0f,0.0f,1.0f); //rojo
		if(i==1) key_color = glm::vec4(1.0f,1.0f,0.0f,1.0f); //amarillo
		if(i==2) key_color = glm::vec4(0.0f,1.0f,0.0f,1.0f); //verde
		if(i==3) key_color = glm::vec4(0.2f,0.2f,1.0f,1.0f); //azul
		if(i==4) key_color = glm::vec4(1.0f,0.0f,1.0f,1.0f); //violeta

		target_keys[i].DrawLevitating(camera,&shader,&model,&data, key_color, i);
	}
	
	Coord P; P.x = player.GetX(); P.y = player.GetY(); P.z = player.GetZ();
	float r = RADIUS;

	if(pickedkey_id != -1)
	{
		if( columns[pickedkey_id].InsideGatheringArea(P.x,P.y,P.z) )
		{
			//Sound.Play(SOUND_UNLOCK);
			//Sound.Play(SOUND_ENERGYFLOW);
			target_keys[pickedkey_id].Deploy();
			pickedkey_id = -1;
			if(respawn_id)
			{
				//Sound.Play(SOUND_SWISH);
				respawn_id = 0;
			}
			bool all_keys_deployed = true;
			for(unsigned int i=0; all_keys_deployed && i<target_keys.size(); i++) all_keys_deployed = target_keys[i].IsDeployed();
			portal_activated = all_keys_deployed;
			//if(portal_activated) Sound.Play(SOUND_WARP);
		}
	}

	for(unsigned int i=0; i<columns.size(); i++) columns[i].Draw(&shader,&model,&data,camera,i);

	//draw respawn points
	for(unsigned int i=0; i<respawn_points.size(); i++)
	{
		if(i==respawn_id) respawn_points[i].Draw(data.GetID(IMG_CIRCLE_ON),true,&shader,camera);
		else respawn_points[i].Draw(data.GetID(IMG_CIRCLE_OFF),false,&shader,camera);
	}

	//draw portal
	portal.Draw(&data,portal_activated,&shader,&model,camera);

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
