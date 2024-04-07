#include "ge_column.h"

Column::Column(){}
Column::~Column(){}

void Column::Draw(Shader *shader,Model *column_model,Data *data,Camera *camera,int id)
{
	char texture1[] = "texture1\0";
	char texture2[] = "texture2\0";

	//ang = fmod(ang+LEVITATION_SPEED/20,360);

    glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    if(id==0) color = glm::vec4(1.0f,0.0f,0.0f,1.0f); //rojo
	if(id==1) color = glm::vec4(1.0f,1.0f,0.0f,1.0f); //amarillo
	if(id==2) color = glm::vec4(0.0f,1.0f,0.0f,1.0f); //verde
	if(id==3) color = glm::vec4(0.1f,0.1f,1.0f,1.0f); //azul
	if(id==4) color = glm::vec4(1.0f,0.0f,1.0f,1.0f); //violeta

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view =  camera->GetViewMatrix(); // remove translation from the view matrix
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)camera->SCR_WIDTH/(float)camera->SCR_HEIGHT, 0.1f, 1000.0f);

   	model = glm::translate(model, glm::vec3(x,y,z));
   	//model = glm::translate(model, glm::vec3(0,COLUMN_HEIGHT+ENERGY_BALL_RADIUS,0));
	model = glm::rotate(model, yaw, glm::vec3(0.0f,1.0f,0.0f));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_COLUMN));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_COLUMN_NMAP));
	shader->Activate(PROGRAM_KEY);
	shader->setInt(texture1, 0);
	shader->setInt(texture2, 0);
	shader->setVec4("ourColor", color);
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);


	column_model->Draw(MODEL_COLUMN);



	// glPushMatrix();

	// glTranslatef(x,y,z);
	// glRotatef(yaw,0.0f,1.0f,0.0f);

	// glEnable(GL_TEXTURE_2D);
	// glActiveTexture(GL_TEXTURE0);
	// glBindTexture(GL_TEXTURE_2D,data->GetID(IMG_COLUMN));
	// glActiveTexture(GL_TEXTURE1);
	// glBindTexture(GL_TEXTURE_2D,data->GetID(IMG_COLUMN_NMAP));
	// glDisable(GL_TEXTURE_2D);
	// glActiveTexture(GL_TEXTURE0);

	// shader->Activate(PROGRAM_COMPLEX_NORMALMAP);
	// shader->SetUniform("colorMap", 0);
	// shader->SetUniform("normalMap", 1);
	// shader->SetUniform("invRadius", 0.0f);
	// shader->SetUniform("alpha", 1.0f);
	// model->Draw(MODEL_COLUMN);
	// shader->Deactivate();

	// //color dye
	// if(id==0) glColor3f(1.0f,0.0f,0.0f); //rojo
	// if(id==1) glColor3f(1.0f,1.0f,0.0f); //amarillo
	// if(id==2) glColor3f(0.0f,1.0f,0.0f); //verde
	// if(id==3) glColor3f(0.1f,0.1f,1.0f); //azul
	// if(id==4) glColor3f(1.0f,0.0f,1.0f); //violeta

	// glTranslatef(0,COLUMN_HEIGHT+ENERGY_BALL_RADIUS,0);

	// glEnable(GL_BLEND);
	// GLUquadricObj *q = gluNewQuadric();

	// shader->Activate(PROGRAM_SIMPLE_LIGHTBALL);
	// gluSphere(q,ENERGY_BALL_RADIUS,32,32);
	// shader->Deactivate();

	// gluDeleteQuadric(q);
	// glDisable(GL_BLEND);

	// glColor4f(1,1,1,1);

	// glPopMatrix();
}

void Column::SetColumn(float posx, float posy, float posz, float ang)
{
	x = posx;
	y = posy;
	z = posz;
	yaw = ang;
}
bool Column::InsideGatheringArea(float posx, float posy, float posz)
{
	if(yaw == -90)
		return (posz <= z + GATHERNG_AREA_SIDE/2 && posz >= z - GATHERNG_AREA_SIDE/2 && posx <= x && posx >= x - GATHERNG_AREA_SIDE);
	else if(yaw == 90)
		return (posz <= z + GATHERNG_AREA_SIDE/2 && posz >= z - GATHERNG_AREA_SIDE/2 && posx <= x + GATHERNG_AREA_SIDE && posx >= x);
	else //if(yaw == 180)
		return (posz <= z && posz >= z - GATHERNG_AREA_SIDE && posx <= x + GATHERNG_AREA_SIDE/2 && posx >= x - GATHERNG_AREA_SIDE/2);
}

float Column::GetX()
{
	return x;
}
float Column::GetY()
{
	return y;
}
float Column::GetZ()
{
	return z;
}
float Column::GetHoleX()
{
	if(yaw == -90) return x - 1.5f;
	else if(yaw == 90)  return x + 1.5f;
	else /*if(yaw == 180)*/ return x;
}
float Column::GetHoleY()
{
	return y + 1.0f;
}
float Column::GetHoleZ()
{
	if(yaw == 180) return z - 1.5f;
	else return z;
}
float Column::GetYaw()
{
	return yaw;
}