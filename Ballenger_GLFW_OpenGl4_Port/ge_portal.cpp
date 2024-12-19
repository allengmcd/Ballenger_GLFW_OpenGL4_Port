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
