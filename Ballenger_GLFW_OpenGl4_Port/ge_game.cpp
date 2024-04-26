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
	window = newWindow;
	bool res = true;
	noclip = false;
	portal_activated = false;
	time = ang = 0.0f;
	noclipSpeedF = 1.0f; 
	level = lvl;
	state = STATE_RUN;
	respawn_id = 0;
	pickedkey_id = -1;
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
	rp.Load();
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

	player_camera = new Camera(glm::vec3(0.0f, 10.0f, 3.0f));
	debug_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	camera = player_camera;


	EnergyBeacon *energyBeaconTemp = new EnergyBeacon();

	energyBeaconTemp->Load(16,75, 5000);
	energyBeaconTemp->SetEnergyBeacon(player.GetX(),player.GetY(),player.GetZ(),0.0f);

	energyBeacon = *energyBeaconTemp;
	//energyBeacon = energyBeaconTemp;

	//sound.Play(SOUND_AMBIENT); //TODO: this causes segfault
	//sound.PlayBounce(.25f); //TODO: So does this

	//return res;
	return 1;
}

bool Game::Process()
{
		bool res=true;
	
	//Process Input
	if(keys[27])	res=false;

	glm::vec3 directionVector =camera->Front;
	float vx,vy,vz;
	//camera->GetDirectionVector(vx,vy,vz);
	vx = directionVector.x;
	vy = directionVector.y;
	vz = directionVector.z;
	float factor = sqrt( 1.0f/(vx*vx + vz*vz) );

	if(keys['1']) camera->SetState(STATE_FPS);
	player.SetFade(!keys['2']);
	if(keys['3']) camera->SetState(STATE_TPS);

	if(noclip)
	{
		if(keys[P_UP])
		{
			player.SetX(player.GetX() + noclipSpeedF*vx);
			player.SetY(player.GetY() + noclipSpeedF*vy);
			player.SetZ(player.GetZ() + noclipSpeedF*vz);
			if(camera->GetState() == STATE_TPS_FREE) camera->LastYaw = camera->Yaw;//camera->SetLastYaw(camera->GetYaw());
		}
		else if(keys[P_DOWN])
		{
			player.SetX(player.GetX() - noclipSpeedF*vx);
			player.SetY(player.GetY() - noclipSpeedF*vy);
			player.SetZ(player.GetZ() - noclipSpeedF*vz);
			if(camera->GetState() == STATE_TPS_FREE) camera->LastYaw = camera->Yaw-PI;//camera->SetLastYaw(camera->GetYaw()-PI);
		}
		if(keys[P_LEFT])
		{
			player.SetX(player.GetX() + noclipSpeedF*vz*factor);
			player.SetZ(player.GetZ() - noclipSpeedF*vx*factor);
			if(camera->GetState() == STATE_TPS_FREE)
			{
				if(keys['w']) camera->LastYaw = camera->Yaw-PI/4;//camera->SetLastYaw(camera->GetYaw()-PI/4);
				else if (keys['s']) camera->LastYaw = camera->Yaw-(PI*3)/4; //camera->SetLastYaw(camera->GetYaw()-(PI*3)/4);
				else camera->LastYaw = camera->Yaw-PI/2;//camera->SetLastYaw(camera->GetYaw()-PI/2);
			}
		}
		else if(keys[P_RIGHT])
		{
			player.SetX(player.GetX() - noclipSpeedF*vz*factor);
			player.SetZ(player.GetZ() + noclipSpeedF*vx*factor);
			if(camera->GetState() == STATE_TPS_FREE)
			{
				if(keys['w']) camera->LastYaw = camera->Yaw+PI/4;//camera->SetLastYaw(camera->GetYaw()+PI/4);
				else if (keys['s']) camera->LastYaw = camera->Yaw+(PI*3)/4;//camera->SetLastYaw(camera->GetYaw()+(PI*3)/4);
				else camera->LastYaw = camera->Yaw+PI/2;//camera->SetLastYaw(camera->GetYaw()+PI/2);
			}
		}
		if(mouse_left_down) player.SetY(player.GetY() + noclipSpeedF);
		else if(mouse_right_down) player.SetY(player.GetY() - noclipSpeedF);
		if(keys[P_PLUS])
		{
			noclipSpeedF += 0.01f;
			if(noclipSpeedF > 2.0f) noclipSpeedF = 2.0f;
		}
		else if(keys[P_MINUS])
		{
			noclipSpeedF -= 0.01f;
			if(noclipSpeedF < 0.05f) noclipSpeedF = 0.05f;
		}
	}
	else
	{
		if(keys[P_UP])
		{
			float nextVX = player.GetVX() + PLAYER_SPEED*vx*factor;
			float nextVZ = player.GetVZ() + PLAYER_SPEED*vz*factor;
			float limitation_factor;
			if( sqrt(nextVX*nextVX + nextVZ*nextVZ) <= MAX_MOVEMENT ) limitation_factor = 1.0f;
			else limitation_factor = sqrt( (MAX_MOVEMENT*MAX_MOVEMENT)/(nextVX*nextVX + nextVZ*nextVZ) );
			player.SetVX(nextVX*limitation_factor);
			player.SetVZ(nextVZ*limitation_factor);

			if(camera->GetState() == STATE_TPS_FREE) camera->LastYaw = camera->Yaw;//camera->SetLastYaw(camera->GetYaw());
		}
		else if(keys[P_DOWN])
		{
			float nextVX = player.GetVX() - PLAYER_SPEED*vx*factor;
			float nextVZ = player.GetVZ() - PLAYER_SPEED*vz*factor;
			float limitation_factor;
			if( sqrt(nextVX*nextVX + nextVZ*nextVZ) <= MAX_MOVEMENT ) limitation_factor = 1.0f;
			else limitation_factor = sqrt( (MAX_MOVEMENT*MAX_MOVEMENT)/(nextVX*nextVX + nextVZ*nextVZ) );
			player.SetVX(nextVX*limitation_factor);
			player.SetVZ(nextVZ*limitation_factor);

			if(camera->GetState() == STATE_TPS_FREE) camera->LastYaw = camera->Yaw-PI;// camera->SetLastYaw(camera->GetYaw()-PI);
		}
		if(keys[P_LEFT])
		{
			float nextVX = player.GetVX() + PLAYER_SPEED*vz*factor;
			float nextVZ = player.GetVZ() - PLAYER_SPEED*vx*factor;
			float limitation_factor;
			if( sqrt(nextVX*nextVX + nextVZ*nextVZ) <= MAX_MOVEMENT ) limitation_factor = 1.0f;
			else limitation_factor = sqrt( (MAX_MOVEMENT*MAX_MOVEMENT)/(nextVX*nextVX + nextVZ*nextVZ) );
			player.SetVX(nextVX*limitation_factor);
			player.SetVZ(nextVZ*limitation_factor);

			if(camera->GetState() == STATE_TPS_FREE)
			{
				if(keys['w']) camera->LastYaw = camera->Yaw-PI/4;//camera->SetLastYaw(camera->GetYaw()-PI/4);
				else if (keys['s']) camera->LastYaw = camera->Yaw-(PI*3)/4;//camera->SetLastYaw(camera->GetYaw()-(PI*3)/4);
				else camera->LastYaw = camera->Yaw-PI/2;//camera->SetLastYaw(camera->GetYaw()-PI/2);
			}
		}
		else if(keys[P_RIGHT])
		{
			float nextVX = player.GetVX() - PLAYER_SPEED*vz*factor;
			float nextVZ = player.GetVZ() + PLAYER_SPEED*vx*factor;
			float limitation_factor;
			if( sqrt(nextVX*nextVX + nextVZ*nextVZ) <= MAX_MOVEMENT ) limitation_factor = 1.0f;
			else limitation_factor = sqrt( (MAX_MOVEMENT*MAX_MOVEMENT)/(nextVX*nextVX + nextVZ*nextVZ) );
			player.SetVX(nextVX*limitation_factor);
			player.SetVZ(nextVZ*limitation_factor);
			
			if(camera->GetState() == STATE_TPS_FREE)
			{
				if(keys['w']) camera->LastYaw = camera->Yaw+PI/4;//camera->SetLastYaw(camera->GetYaw()+PI/4);
				else if (keys['s']) camera->LastYaw = camera->Yaw+(PI*3)/4;//camera->SetLastYaw(camera->GetYaw()+(PI*3)/4);
				else camera->LastYaw = camera->Yaw+PI/2;//camera->SetLastYaw(camera->GetYaw()+PI/2);
			}
		}
		if(keys[P_JUMP])
		{
			if(player.GetY()-RADIUS < terrain.GetHeight(player.GetX(),player.GetZ())+0.01f)
			{
				player.SetVY(PLAYER_JUMP_SPEED);
				//Sound.PlayBounce(1.0f);
			}
		}

		float initial_z = player.GetZ();
		Physics(player);

		//comprueba si el player muere
		if(player.GetY() <= lava.GetHeight()+RADIUS)
		{
			player.SetY(lava.GetHeight()+RADIUS);
			player.SetVel(0.0f,0.0f,0.0f);
			pickedkey_id = -1;
			state = STATE_LIVELOSS;
			//Sound.Play(SOUND_SWISH);
		}

		Coord P; P.x = player.GetX(); P.y = player.GetY(); P.z = player.GetZ();
		float r = RADIUS;

		//comprueba si el player entra en algun Respawn Point
		float cr = CIRCLE_RADIUS,ah = AURA_HEIGHT;
		for(unsigned int i=0; i<respawn_points.size(); i++)
		{
			Coord RP; RP.x = respawn_points[i].GetX(); RP.y = respawn_points[i].GetY(); RP.z = respawn_points[i].GetZ(); 
			if( sqrt((P.x-RP.x)*(P.x-RP.x) + (P.y-RP.y)*(P.y-RP.y) + (P.z-RP.z)*(P.z-RP.z)) <= RADIUS+CIRCLE_RADIUS)
			{
				//if(respawn_id != i) Sound.Play(SOUND_SWISH);
				respawn_id = i;
			}
		}

		//comprueba si el player recoge alguna llave
		if(pickedkey_id == -1)
		{
			for(unsigned int i=0; i<target_keys.size(); i++)
			{
				if(!target_keys[i].IsDeployed())
				{
					Coord K; K.x = target_keys[i].GetX(); K.y = target_keys[i].GetY(); K.z = target_keys[i].GetZ(); 
					if( sqrt((P.x-K.x)*(P.x-K.x) + (P.y-K.y)*(P.y-K.y) + (P.z-K.z)*(P.z-K.z)) <= RADIUS*2)
					{
						pickedkey_id = i;
						//Sound.Play(SOUND_PICKUP);
					}
				}
			}
		}

		//comprueba si el player llega con una llave a su respectiva columna
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

		//comprueba si el player atraviesa el portal estando activado
		if(portal_activated)
		{
			if( portal.InsidePortal(P.x,P.y,P.z,RADIUS) )
			{
				if( (initial_z-portal.GetZ() <= 0.0f && player.GetZ()-portal.GetZ() >= 0.0f) || 
				    (initial_z-portal.GetZ() >= 0.0f && player.GetZ()-portal.GetZ() <= 0.0f)  ) state = STATE_ENDGAME;
			}
		}
	}

	// //limpio buffer de sonidos
	// Sound.Update();

	return res;
}

bool Game::Loop()
{
	bool res=true;

	// Process();
	// Render();

	if(state == STATE_RUN)
	{
		res = Process();
		if(res) Render();
	}
	else if(state == STATE_LIVELOSS)
	{
		Render();
		player.SetPos(respawn_points[respawn_id].GetX(),respawn_points[respawn_id].GetY()+RADIUS,respawn_points[respawn_id].GetZ());
		state = STATE_RUN;
	}
	else if(state == STATE_ENDGAME)
	{
		res=false;
	}

	return res;
}

void Game::Finalize()
{
}
 
void Game::Physics(Bicho &object)
{
	Coord initialPos; initialPos.x = object.GetX(); initialPos.y = object.GetY(); initialPos.z = object.GetZ();
	Coord center; center.x = object.GetX() + object.GetVX(); center.y = object.GetY() + object.GetVY(); center.z = object.GetZ() + object.GetVZ();
	std::vector<Vector> cnormals = terrain.GetCollisionNormals(center,RADIUS);
	object.SetPos(center.x,center.y,center.z); //despues de GetCollisionNormals la posicion center sera una posicion valida sobre la superficie

	//actualizo angulos de rotacion por movimiento
	if(object.GetZ() != initialPos.z || object.GetX() != initialPos.x)
	{
		float yaw,pitch;
		float dx = abs(abs(object.GetX()) - abs(initialPos.x)), dz = abs(abs(object.GetZ()) - abs(initialPos.z));
		if(object.GetZ() > initialPos.z && object.GetX() >= initialPos.x) yaw = atan( dx / dz ); //primer cuadrante
		if(object.GetZ() <= initialPos.z && object.GetX() > initialPos.x) yaw = PI/2 + atan( dz / dx ); //segundo cuadrante
		if(object.GetZ() < initialPos.z && object.GetX() <= initialPos.x) yaw = PI + atan( dx / dz );//tercer cuadrante
		if(object.GetZ() >= initialPos.z && object.GetX() < initialPos.x) yaw = PI*3/2 + atan( dz / dx );//cuarto cuadrante
		object.SetYaw(yaw*(180/PI));

		float perimeter = PI*2*RADIUS;
		float dy = abs(abs(object.GetY()) - abs(initialPos.y));
		float travel_dist = sqrt( dx*dx + dy*dy + dz*dz );
		if(cos(yaw) >= 0.0f) pitch = object.GetPitch() + (travel_dist/perimeter) * 360.0f;
		else pitch = object.GetPitch() - (travel_dist/perimeter) * 360.0f;
		if(pitch < 0.0f) pitch = 360.0f - abs(pitch);
		object.SetPitch(fmod(pitch,360.0f));
	}

	if(cnormals.empty()) object.SetVY(object.GetVY() - GRAVITY);
	else
	{
		Vector G,F,G1,F1,cNormal;
		float rz,rx; //angulos de rotacion
		float factor,N = 0.0f;

		G.x = 0.0f; G.y = -GRAVITY; G.z = 0.0f;
		F.x = object.GetVX(); F.y = object.GetVY(); F.z = object.GetVZ();
		cNormal.x = 0.0f; cNormal.y = 0.0f; cNormal.z = 0.0f;

		for(unsigned int i=0; i<cnormals.size(); i++)
		{
			if(cnormals[i].x == 0.0f) rz = 0.0f;
			else if(cnormals[i].x >  0.0f) rz = -PI/2 + atan(cnormals[i].y/cnormals[i].x);
			else rz = PI/2 + atan(cnormals[i].y/cnormals[i].x);

			if(cnormals[i].z == 0.0f) rx = 0.0f;
			else if(cnormals[i].z >  0.0f) rx = PI/2 - atan(cnormals[i].y/cnormals[i].z);
			else rx = -PI/2 - atan(cnormals[i].y/cnormals[i].z);

			//Transformamos las fuerzas definidas en el sistema de coordenadas de OpenGL al sistema de coordenadas definido por cnormal(eje y) 
			G1.x = cos(-rz)*G.x - sin(-rz)*G.y;
			G1.y = cos(-rx)*sin(-rz)*G.x + cos(-rx)*cos(-rz)*G.y - sin(-rx)*G.z;
			G1.z = sin(-rx)*sin(-rz)*G.x + sin(-rx)*cos(-rz)*G.y + cos(-rx)*G.z;

			F1.x = cos(-rz)*F.x - sin(-rz)*F.y;
			F1.y = cos(-rx)*sin(-rz)*F.x + cos(-rx)*cos(-rz)*F.y - sin(-rx)*F.z;
			F1.z = sin(-rx)*sin(-rz)*F.x + sin(-rx)*cos(-rz)*F.y + cos(-rx)*F.z;
			
			//consideramos la fuerza normal para un unico triangulo
			float cN = 0.0f;
			if (G1.y < 0.0f) {cN -= G1.y; G1.y = 0.0f;}
			if (F1.y < 0.0f) {cN -= F1.y; F1.y = 0.0f;}
			N += cN; //actualizo la fuerza normal global

			//actualizo la fuerza de cnormal global
			cNormal.x += cnormals[i].x;
			cNormal.y += cnormals[i].y;
			cNormal.z += cnormals[i].z;

			//consideramos la posible friccion
			if(cN > 0.0f && abs(F1.x) + abs(F1.z) > 0.0f)
			{
				factor = sqrt( ((FRICTION*cN)*(FRICTION*cN)) / (F1.x*F1.x + F1.z*F1.z) );

				if(abs(F1.x) < abs(F1.x*factor)) F1.x = 0.0f;
				else F1.x -= F1.x*factor;

				if(abs(F1.z) < abs(F1.z*factor)) F1.z = 0.0f;
				else F1.z -= F1.z*factor;
			}
			
			//volvemos a Transformar las fuerzas del sistema de coordenadas de cnormal(eje y) al sistema de coordenadas de OpenGL
			G.x = cos(rz)*G1.x - sin(rz)*cos(rx)*G1.y + sin(rz)*sin(rx)*G1.z;
			G.y = sin(rz)*G1.x + cos(rz)*cos(rx)*G1.y - cos(rz)*sin(rx)*G1.z;
			G.z = sin(rx)*G1.y + cos(rx)*G1.z;

			F.x = cos(rz)*F1.x - sin(rz)*cos(rx)*F1.y + sin(rz)*sin(rx)*F1.z;
			F.y = sin(rz)*F1.x + cos(rz)*cos(rx)*F1.y - cos(rz)*sin(rx)*F1.z;
			F.z = sin(rx)*F1.y + cos(rx)*F1.z;
		}

		float nextVX = F.x + G.x;
		float nextVY = F.y + G.y;
		float nextVZ = F.z + G.z;

		//limitaremos la velocidad para que la esfera no se salte triangulos
		float limitation_factor;
		if( sqrt(nextVX*nextVX + nextVY*nextVY + nextVZ*nextVZ) <= MAX_MOVEMENT ) limitation_factor = 1.0f;
		else limitation_factor = sqrt( (MAX_MOVEMENT*MAX_MOVEMENT)/(nextVX*nextVX + nextVY*nextVY + nextVZ*nextVZ) );
		
		nextVX *= limitation_factor;
		nextVY *= limitation_factor;
		nextVZ *= limitation_factor;

		//consideramos el rebote
		if(N > GRAVITY*4) factor = sqrt( (N*N) / (cNormal.x*cNormal.x + cNormal.y*cNormal.y + cNormal.z*cNormal.z) );
		else factor = 0.0f;

		nextVX += cNormal.x*factor*ELASTICITY;
		nextVY += cNormal.y*factor*ELASTICITY;
		nextVZ += cNormal.z*factor*ELASTICITY;
		
		float bounceForce = sqrt( (cNormal.x*factor*ELASTICITY)*(cNormal.x*factor*ELASTICITY) + (cNormal.y*factor*ELASTICITY)*(cNormal.y*factor*ELASTICITY) + (cNormal.z*factor*ELASTICITY)*(cNormal.z*factor*ELASTICITY) );
		//if(bounceForce >= PLAYER_JUMP_SPEED) Sound.PlayBounce(1.0f);
		//else if(bounceForce/PLAYER_JUMP_SPEED > 0.2f) Sound.PlayBounce(bounceForce/PLAYER_JUMP_SPEED);

		//actualizamos velocidad
		object.SetVel(nextVX, nextVY, nextVZ);
	}
}

void Game::Render()
{
	// render
	// ------
	//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if(state != STATE_LIVELOSS) lava.Update();
	playerCamera.Update(player_camera,&terrain, &lava, player.GetX(), player.GetY(), player.GetZ());

	//skybox.Draw(camera);
	//scene.Draw(&terrain,&shader,camera,&data,&lava);

	
	//draw player
	player.Draw(&data,camera,&lava,&shader);

	energyBeacon.Draw(&data,camera,&shader);
	
	
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
	for(unsigned int i=0; i<target_keys.size(); i++)
	{
	// 	//color dye
	// 	if(i==0) glColor3f(1.0f,0.0f,0.0f); //rojo
	// 	if(i==1) glColor3f(1.0f,1.0f,0.0f); //amarillo
	// 	if(i==2) glColor3f(0.0f,1.0f,0.0f); //verde
	// 	if(i==3) glColor3f(0.2f,0.2f,1.0f); //azul
	// 	if(i==4) glColor3f(1.0f,0.0f,1.0f); //violeta

		glm::vec4 key_color = glm::vec4(0.0f,0.0f,0.0f,0.0f);
		//ray color
		if(i==0) key_color = glm::vec4(1.0f,0.0f,0.0f,1.0f); //rojo
		if(i==1) key_color = glm::vec4(1.0f,1.0f,0.0f,1.0f); //amarillo
		if(i==2) key_color = glm::vec4(0.0f,1.0f,0.0f,1.0f); //verde
		if(i==3) key_color = glm::vec4(0.2f,0.2f,1.0f,1.0f); //azul
		if(i==4) key_color = glm::vec4(1.0f,0.0f,1.0f,1.0f); //violeta

		if(i==pickedkey_id) target_keys[i].DrawPicked(player.GetX(),player.GetY(),player.GetZ(),camera->GetYaw(),camera,&shader,&model,&data,key_color);
		else if(target_keys[i].IsDeployed())
		{
			target_keys[i].DrawDeployed(columns[i].GetHoleX(),columns[i].GetHoleY(),columns[i].GetHoleZ(),columns[i].GetYaw(),camera,&model,&data,&shader,key_color);
			
			// //ray color
			// if(i==0) glColor4f(1.0f,0.0f,0.0f,0.4f); //rojo
			// if(i==1) glColor4f(1.0f,1.0f,0.0f,0.4f); //amarillo
			// if(i==2) glColor4f(0.0f,1.0f,0.0f,0.4f); //verde
			// if(i==3) glColor4f(0.2f,0.2f,1.0f,0.4f); //azul
			// if(i==4) glColor4f(1.0f,0.0f,1.0f,0.4f); //violeta

			// float r = ENERGY_BALL_RADIUS/2.0f; //energy ray radius
			// int numrays = 6;
			// glDisable(GL_LIGHTING);
			// for(int j=0; j<numrays; j++)
			// {
			// 	float ang_rad = (ang+j*(360/numrays))*(PI/180);
			// 	glEnable(GL_BLEND);
			// 	glLineWidth(2.0);
			// 	glBegin(GL_LINES);
			// 		glVertex3f(columns[i].GetX()+cos(ang_rad)*r, columns[i].GetY()+COLUMN_HEIGHT+ENERGY_BALL_RADIUS+sin(ang_rad)*r, columns[i].GetZ());
			// 		glVertex3f(Portal.GetReceptorX(i), Portal.GetReceptorY(i), Portal.GetZ());
			// 	glEnd();
			// 	glDisable(GL_BLEND);
			// }
			// glEnable(GL_LIGHTING);
		}
		else
		{
			//float dist = sqrt( (Player.GetX()-target_keys[i].GetX())*(Player.GetX()-target_keys[i].GetX()) + (Player.GetZ()-target_keys[i].GetZ())*(Player.GetZ()-target_keys[i].GetZ()) );

			target_keys[i].DrawLevitating(camera,&shader,&model,&data, key_color, i);
		}

		//glColor4f(1,1,1,1);
	}
	

	glfwSwapBuffers(window);
}

void Game::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	if(key >= 'A' && key <= 'Z') key += 32;
	keys[key] = press;
}

void Game::ReadMouseMotion(int x, int y)
{
	//la cantidad desplazada en pixeles
    int dx = x;// - SCREEN_WIDTH/2;
    int dy = -y;// - SCREEN_HEIGHT/2;

    if(dx) {
        camera->RotateYaw(CAMERA_SPEED*dx);
		if(camera->GetState() != STATE_TPS_FREE) camera->SetLastYaw(camera->GetYaw());
    }

    if(dy) {
        camera->RotatePitch(-CAMERA_SPEED*dy);
    }

}

void Game::ToggleCamera(bool debug_camera_active)
{
	if(debug_camera_active)
	{
		camera = debug_camera;
	}
	else
	{
		camera = player_camera;
	}
}