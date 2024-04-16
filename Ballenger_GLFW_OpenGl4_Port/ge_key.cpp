#include "ge_key.h"

Key::Key()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	ang = 0.0f;
	deployed = false;
}
Key::~Key(){}

void Key::DrawLevitating(Camera *camera, Shader *shader, Model *key_model, Data *data, glm::vec4 color, float dist)
{
	char texture1[] = "texture1\0";
	char texture2[] = "texture2\0";

	ang = fmod(ang+LEVITATION_SPEED/20,360);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view =  camera->GetViewMatrix(); // remove translation from the view matrix
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)camera->SCR_WIDTH/(float)camera->SCR_HEIGHT, 0.1f, 1000.0f);

   	model = glm::translate(model, glm::vec3(x,y+0.5f+(sin(ang*(PI/180)))/2,z));
	model = glm::rotate(model, ang, glm::vec3(0.0f,1.0f,0.0f));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_KEY));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_KEY_NMAP));
	shader->Activate(PROGRAM_KEY);
	shader->setInt(texture1, 0);
	shader->setInt(texture2, 0);
	shader->setVec4("ourColor", color);
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);


	key_model->Draw(MODEL_KEY);
}

void Key::DrawPicked(float playerx,float playery, float playerz, float camera_yaw, Camera *camera, Shader *shader, Model *key_model, Data *data, glm::vec4 color)
{
	// char colorMap_name[] = "colorMap\0";
	// char normalMap_name[] = "normalMap\0";
	// char invRadius_name[] = "invRadius\0";
	// char alpha_name[] = "alpha\0";

	// glPushMatrix();

	// ang = fmod(ang+LEVITATION_SPEED,360);
	// glTranslatef(playerx,playery+0.7,playerz);
	// glRotatef(ang,0.0f,1.0f,0.0f);
	// //glRotatef(camera_yaw*(180/PI),0.0f,1.0f,0.0f);

	// glEnable(GL_TEXTURE_2D);
	// glActiveTexture(GL_TEXTURE0);
	// glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_KEY));
	// glActiveTexture(GL_TEXTURE1);
	// glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_KEY_NMAP));
	// glDisable(GL_TEXTURE_2D);
	// glActiveTexture(GL_TEXTURE0);

	// Shader->Activate(PROGRAM_COMPLEX_NORMALMAP);
	// Shader->SetUniform(colorMap_name, 0);
	// Shader->SetUniform(normalMap_name, 1);
	// Shader->SetUniform(invRadius_name, 0.0f);
	// Shader->SetUniform(alpha_name, 1.0f);
	// Model->Draw(MODEL_KEY);
	// Shader->Deactivate();
	
	// glPopMatrix();

	char texture1[] = "texture1\0";
	char texture2[] = "texture2\0";

	ang = fmod(ang+LEVITATION_SPEED/20,360);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view =  camera->GetViewMatrix(); // remove translation from the view matrix
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)camera->SCR_WIDTH/(float)camera->SCR_HEIGHT, 0.1f, 1000.0f);

   	model = glm::translate(model, glm::vec3(playerx,playery+0.7,playerz));
	//model = glm::rotate(model, ang, glm::vec3(0.0f,1.0f,0.0f));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_KEY));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_KEY_NMAP));
	shader->Activate(PROGRAM_KEY);
	shader->setInt(texture1, 0);
	shader->setInt(texture2, 0);
	shader->setVec4("ourColor", color);
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);


	key_model->Draw(MODEL_KEY);
}

void Key::DrawDeployed(float holex,float holey,float holez, float yaw, Model *Model, Data *Data, Shader *Shader)
{
	// char colorMap_name[] = "colorMap\0";
	// char normalMap_name[] = "normalMap\0";
	// char invRadius_name[] = "invRadius\0";
	// char alpha_name[] = "alpha\0";

	// glPushMatrix();

	// glTranslatef(holex,holey,holez);
	// glRotatef(yaw,0,1,0);
	// glRotatef(180+45,1,0,0);
	// glTranslatef(0,-0.69,0);

	// glEnable(GL_TEXTURE_2D);
	// glActiveTexture(GL_TEXTURE0);
	// glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_KEY));
	// glActiveTexture(GL_TEXTURE1);
	// glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_KEY_NMAP));
	// glDisable(GL_TEXTURE_2D);
	// glActiveTexture(GL_TEXTURE0);

	// Shader->Activate(PROGRAM_COMPLEX_NORMALMAP);
	// Shader->SetUniform(colorMap_name, 0);
	// Shader->SetUniform(normalMap_name, 1);
	// Shader->SetUniform(invRadius_name, 0.0f);
	// Shader->SetUniform(alpha_name, 1.0f);
	// Model->Draw(MODEL_KEY);
	// Shader->Deactivate();
	
	// glPopMatrix();
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