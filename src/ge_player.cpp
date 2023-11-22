#include "ge_player.h"

Player::Player()
{
	fade = true;
}
Player::~Player(){}

void Player::Draw(Data *Data, Camera *Camera, Lava *Lava, Shader *Shader)
{

	char colorMap_name[] = "colorMap\0";
	char normalMap_name[] = "normalMap\0";
	char invRadius_name[] = "invRadius\0";
	char alpha_name[] = "alpha\0";
	char lava_height_name[] = "lava_height\0";
	char posy_name[] = "posy\0";

	glPushMatrix();
	glTranslatef(GetX(),GetY(),GetZ());

	//rotacion por movimiento
	if(cos(GetYaw()*(PI/180)) >= 0.0f) glRotatef(GetPitch(), cos(GetYaw()*(PI/180)),0.0,-sin(GetYaw()*(PI/180)) );
	else glRotatef(GetPitch(), -cos(GetYaw()*(PI/180)),0.0,sin(GetYaw()*(PI/180)) );

	if(Camera->GetState() != STATE_FPS)
	{
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_PLAYER));
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_PLAYER_NMAP));
		glDisable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);

		glEnable(GL_BLEND);
		GLUquadricObj *q = gluNewQuadric();
		gluQuadricTexture(q,true);

		Shader->Activate(PROGRAM_LAVAGLOW);
		Shader->SetUniform(colorMap_name, 0);
		Shader->SetUniform(normalMap_name, 1);
		Shader->SetUniform(invRadius_name, 0.0f);
		if(fade) Shader->SetUniform(alpha_name, Camera->GetDistance()/3.0f);
		else Shader->SetUniform(alpha_name, 1.0f);
		Shader->SetUniform(lava_height_name, Lava->GetHeight());
		Shader->SetUniform(posy_name, GetY()-RADIUS);
		gluSphere(q,RADIUS,16,16);
		Shader->Deactivate();

		gluDeleteQuadric(q);
		glDisable(GL_BLEND);
	}

	glPopMatrix();
}

void Player::SetFade(bool b)
{
	fade = b;
}