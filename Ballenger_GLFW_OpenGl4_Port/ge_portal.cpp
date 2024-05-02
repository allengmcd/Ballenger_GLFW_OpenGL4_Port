#include "ge_portal.h"

Portal::Portal(){}
Portal::~Portal(){}

void Portal::Draw(Data *data, bool activated, Shader *shader, Model *portal_model, Camera *camera)
{
	char texture1[] = "texture1\0";
	char texture2[] = "texture2\0";

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view =  camera->GetViewMatrix(); // remove translation from the view matrix
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)camera->SCR_WIDTH/(float)camera->SCR_HEIGHT, 0.1f, 1000.0f);

   	model = glm::translate(model, glm::vec3(x,y,z));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_PORTAL));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_PORTAL_NMAP));
	shader->Activate(PROGRAM_KEY);
	shader->setInt(texture1, 0);
	shader->setInt(texture2, 0);
	shader->setVec4("ourColor", glm::vec4(0.0f,0.0f,0.0f,1.0f));
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);
	shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	shader->setVec3("lightPos", glm::vec3(50.0f, 50.0f, 50.0f));
	shader->setVec3("viewPos", camera->Position);


	portal_model->Draw(MODEL_PORTAL);

	// //vortex
	// if(activated)
	// {
	// 	glPushMatrix();

	// 	glTranslatef(x,y,z);
	// 	ang = fmod(ang+PORTAL_SPEED,360);
	// 	glTranslatef(0,PORTAL_SIDE/2,0);
	// 	glRotatef(ang,0.0f,0.0f,1.0f);
		
	// 	glDisable(GL_LIGHTING);
	// 	glEnable(GL_TEXTURE_2D);
	// 	glEnable(GL_BLEND);
	// 	glDisable(GL_CULL_FACE);
	// 	glBindTexture(GL_TEXTURE_2D,data->GetID(IMG_VORTEX));
	// 	glBegin(GL_QUADS);
	// 		glTexCoord2f(0.0f, 1.0f); glVertex3f( PORTAL_SIDE/2,-PORTAL_SIDE/2, 0);
	// 		glTexCoord2f(1.0f, 1.0f); glVertex3f(-PORTAL_SIDE/2,-PORTAL_SIDE/2, 0);
	// 		glTexCoord2f(1.0f, 0.0f); glVertex3f(-PORTAL_SIDE/2, PORTAL_SIDE/2, 0);
	// 		glTexCoord2f(0.0f, 0.0f); glVertex3f( PORTAL_SIDE/2, PORTAL_SIDE/2, 0);
	// 	glEnd();
	// 	glEnable(GL_CULL_FACE);
	// 	glDisable(GL_BLEND);
	// 	glDisable(GL_TEXTURE_2D);
	// 	glEnable(GL_LIGHTING);

	// 	glPopMatrix();
	// }
	// //f.vortex

	// //portal
	// glPushMatrix();

	// glTranslatef(x,y,z);

	// glEnable(GL_TEXTURE_2D);
	// glActiveTexture(GL_TEXTURE0);
	// glBindTexture(GL_TEXTURE_2D,data->GetID(IMG_PORTAL));
	// glActiveTexture(GL_TEXTURE1);
	// glBindTexture(GL_TEXTURE_2D,data->GetID(IMG_PORTAL_NMAP));
	// glDisable(GL_TEXTURE_2D);
	// glActiveTexture(GL_TEXTURE0);

	// shader->Activate(PROGRAM_COMPLEX_NORMALMAP);
	// shader->SetUniform("colorMap", 0);
	// shader->SetUniform("normalMap", 1);
	// shader->SetUniform("invRadius", 0.0f);
	// shader->SetUniform("alpha", 1.0f);
	// model->Draw(MODEL_PORTAL);
	// shader->Deactivate();
	
	// glEnable(GL_BLEND);
	// GLUquadricObj *q = gluNewQuadric();

	// glTranslatef(0,PORTAL_SIDE*3/2,0);
	// glColor3f(0.0f,1.0f,0.0f); //verde
	// shader->Activate(PROGRAM_SIMPLE_LIGHTBALL);
	// gluSphere(q,0.2,16,16);
	// shader->Deactivate();

	// glTranslatef(PORTAL_SIDE/2,-PORTAL_SIDE/2,0);
	// glColor3f(1.0f,1.0f,0.0f); //amarillo
	// shader->Activate(PROGRAM_SIMPLE_LIGHTBALL);
	// gluSphere(q,0.2,16,16);
	// shader->Deactivate();

	// glTranslatef(-PORTAL_SIDE,0,0);
	// glColor3f(0.2f,0.2f,1.0f); //azul
	// shader->Activate(PROGRAM_SIMPLE_LIGHTBALL);
	// gluSphere(q,0.2,16,16);
	// shader->Deactivate();

	// glTranslatef(0,-(PORTAL_SIDE-1),0);
	// glColor3f(1.0f,0.0f,1.0f); //violeta
	// shader->Activate(PROGRAM_SIMPLE_LIGHTBALL);
	// gluSphere(q,0.2,16,16);
	// shader->Deactivate();

	// glTranslatef(PORTAL_SIDE,0,0);
	// glColor3f(1.0f,0.0f,0.0f); //rojo
	// shader->Activate(PROGRAM_SIMPLE_LIGHTBALL);
	// gluSphere(q,0.2,16,16);
	// shader->Deactivate();

	// gluDeleteQuadric(q);
	// glDisable(GL_BLEND);

	// glColor4f(1,1,1,1);

	// glPopMatrix();
	// //f.portal
}

void Portal::SetPos(float posx, float posy, float posz)
{
	x = posx;
	y = posy;
	z = posz;

	//rojo
	receptors[0].first  = x + PORTAL_SIDE/2;
	receptors[0].second = y + 1.0f;
	//amarillo
	receptors[1].first  = x + PORTAL_SIDE/2;
	receptors[1].second = y + PORTAL_SIDE;
	//verde
	receptors[2].first  = x;
	receptors[2].second = y + PORTAL_SIDE*3/2;
	//azul
	receptors[3].first  = x - PORTAL_SIDE/2;
	receptors[3].second = y + PORTAL_SIDE;
	//violeta
	receptors[4].first  = x - PORTAL_SIDE/2;
	receptors[4].second = y + 1.0f;
}

bool Portal::InsidePortal(float px, float py, float pz, float r)
{
    return ( (px-r <= x+(PORTAL_SIDE/2) && px+r >= x-(PORTAL_SIDE/2)) && (py-r <= y+PORTAL_SIDE && py+r >= y) );
}

float Portal::GetX()
{
	return x;
}
float Portal::GetY()
{
	return y;
}
float Portal::GetZ()
{
	return z;
}
float Portal::GetReceptorX(int i)
{
	return receptors[i].first;
}
float Portal::GetReceptorY(int i)
{
	return receptors[i].second;
}