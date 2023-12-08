#include "ge_key.h"

Key::Key()
{
	ang = 0.0f;
	deployed = false;
}
Key::~Key(){}

void Key::DrawLevitating(Shader *Shader, Model *Model, Data *Data, float dist)
{
	GLUquadricObj *q = gluNewQuadric();


	char colorMap_name[] = "colorMap\0";
	char normalMap_name[] = "normalMap\0";
	char invRadius_name[] = "invRadius\0";
	char alpha_name[] = "alpha\0";
	char hmax_name[] = "hmax\0";

	//key
	glPushMatrix();

	ang = fmod(ang+LEVITATION_SPEED,360);
	glTranslatef(x,y+0.5f+(sin(ang*(PI/180)))/2,z);
	glRotatef(ang,0.0f,1.0f,0.0f);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_KEY));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_KEY_NMAP));
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);

	Shader->Activate(PROGRAM_COMPLEX_NORMALMAP);
	Shader->SetUniform(colorMap_name, 0);
	Shader->SetUniform(normalMap_name, 1);
	Shader->SetUniform(invRadius_name, 0.0f);
	Shader->SetUniform(alpha_name, 1.0f);
	Model->Draw(MODEL_KEY);
	Shader->Deactivate();

	glPopMatrix();
	//f.key

	//beacon
	glPushMatrix();

	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE); //desactivo la escritura en el zbuffer (me aprovecho del algoritmo del pintor para que todos los triangulos se pinten en el orden que le toca [ssi estan a la vista])
	glDisable(GL_CULL_FACE);
	glTranslatef(x,y,z);
	glRotatef(-90,1.0f,0.0f,0.0f);

	Shader->Activate(PROGRAM_SIMPLE_LIGHTBEAM);
	Shader->SetUniform(hmax_name, BEACON_HEIGHT-y);
	if(dist/100 < BEACON_MIN_RADIUS) gluCylinder(q,BEACON_MIN_RADIUS,BEACON_MIN_RADIUS,BEACON_HEIGHT-y,16,16);
	else gluCylinder(q,dist/100,dist/100,BEACON_HEIGHT-y,16,16);
	Shader->Deactivate();

	gluDeleteQuadric(q);
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);

	glPopMatrix();
	//f.beacon
}

void Key::DrawPicked(float playerx,float playery, float playerz, float camera_yaw, Model *Model, Data *Data, Shader *Shader)
{
	char colorMap_name[] = "colorMap\0";
	char normalMap_name[] = "normalMap\0";
	char invRadius_name[] = "invRadius\0";
	char alpha_name[] = "alpha\0";

	glPushMatrix();

	ang = fmod(ang+LEVITATION_SPEED,360);
	glTranslatef(playerx,playery+0.7,playerz);
	glRotatef(ang,0.0f,1.0f,0.0f);
	//glRotatef(camera_yaw*(180/PI),0.0f,1.0f,0.0f);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_KEY));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_KEY_NMAP));
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);

	Shader->Activate(PROGRAM_COMPLEX_NORMALMAP);
	Shader->SetUniform(colorMap_name, 0);
	Shader->SetUniform(normalMap_name, 1);
	Shader->SetUniform(invRadius_name, 0.0f);
	Shader->SetUniform(alpha_name, 1.0f);
	Model->Draw(MODEL_KEY);
	Shader->Deactivate();
	
	glPopMatrix();
}

void Key::DrawDeployed(float holex,float holey,float holez, float yaw, Model *Model, Data *Data, Shader *Shader)
{
	char colorMap_name[] = "colorMap\0";
	char normalMap_name[] = "normalMap\0";
	char invRadius_name[] = "invRadius\0";
	char alpha_name[] = "alpha\0";

	glPushMatrix();

	glTranslatef(holex,holey,holez);
	glRotatef(yaw,0,1,0);
	glRotatef(180+45,1,0,0);
	glTranslatef(0,-0.69,0);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_KEY));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_KEY_NMAP));
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);

	Shader->Activate(PROGRAM_COMPLEX_NORMALMAP);
	Shader->SetUniform(colorMap_name, 0);
	Shader->SetUniform(normalMap_name, 1);
	Shader->SetUniform(invRadius_name, 0.0f);
	Shader->SetUniform(alpha_name, 1.0f);
	Model->Draw(MODEL_KEY);
	Shader->Deactivate();
	
	glPopMatrix();
}

void Key::SetPos(float posx, float posy, float posz)
{
	x = posx;
	y = posy;
	z = posz;
}
float Key::GetX()
{
    return x;
}
float Key::GetY()
{
    return y;
}
float Key::GetZ()
{
    return z;
}
void Key::Deploy()
{
	deployed = true;
}
bool Key::IsDeployed()
{
	return deployed;
}