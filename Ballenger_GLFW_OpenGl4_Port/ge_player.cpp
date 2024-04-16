#include "ge_player.h"

Player::Player()
{
	fade = true;
}
Player::~Player(){}

void Player::Load()
{

	glGenVertexArrays(1, &playerVAO);

	unsigned int vbo, ebo;
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	const unsigned int X_SEGMENTS = 64;
	const unsigned int Y_SEGMENTS = 64;
	//const float PI = 3.14159265359f;
	for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
	{
		for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI)/2;
			float yPos = std::cos(ySegment * PI)/2;
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI)/2;

			positions.push_back(glm::vec3(xPos, yPos, zPos));
			uv.push_back(glm::vec2(xSegment, ySegment));
			normals.push_back(glm::vec3(xPos, yPos, zPos));
		}
	}

	bool oddRow = false;
	for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
	{
		if (!oddRow) // even rows: y == 0, y == 2; and so on
		{
			for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
			{
				indices.push_back(y * (X_SEGMENTS + 1) + x);
				indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
			}
		}
		else
		{
			for (int x = X_SEGMENTS; x >= 0; --x)
			{
				indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				indices.push_back(y * (X_SEGMENTS + 1) + x);
			}
		}
		oddRow = !oddRow;
	}
	indexCount = static_cast<unsigned int>(indices.size());

	std::vector<float> data;
	for (unsigned int i = 0; i < positions.size(); ++i)
	{
		data.push_back(positions[i].x);
		data.push_back(positions[i].y);
		data.push_back(positions[i].z);
		if (normals.size() > 0)
		{
			data.push_back(normals[i].x);
			data.push_back(normals[i].y);
			data.push_back(normals[i].z);
		}
		if (uv.size() > 0)
		{
			data.push_back(uv[i].x);
			data.push_back(uv[i].y);
		}
	}
	glBindVertexArray(playerVAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	unsigned int stride = (3 + 2 + 3) * sizeof(float);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));

}

void Player::Draw(Data *data, Camera *camera, Lava *lava, Shader *shader)
{

	char colorMap_name[] = "colorMap\0";
	char normalMap_name[] = "normalMap\0";
	char invRadius_name[] = "invRadius\0";
	char alpha_name[] = "alpha\0";
	char lava_height_name[] = "lava_height\0";
	char posy_name[] = "posy\0";

	char texture1[] = "texture1\0";
	char texture2[] = "texture2\0";

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view =  camera->GetViewMatrix(); // remove translation from the view matrix
	glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)camera->SCR_WIDTH/(float)camera->SCR_HEIGHT, 0.1f, 1000.0f);


    model = glm::translate(model, glm::vec3(GetX(), GetY(), GetZ()));
	model = glm::rotate(model, -GetPitch()/100, glm::vec3(-cos(GetYaw()*(PI/180))/100,0.0,sin(GetYaw()*(PI/180))/100));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_PLAYER));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_PLAYER_NMAP));
	shader->Activate(PROGRAM_PLAYER);
	shader->setInt(texture1, 0);
	shader->setInt(texture2, 0);
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

   	glBindVertexArray(playerVAO);
    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	// glPushMatrix();
	// glTranslatef(GetX(),GetY(),GetZ());

	// //rotacion por movimiento
	// if(cos(GetYaw()*(PI/180)) >= 0.0f) glRotatef(GetPitch(), cos(GetYaw()*(PI/180)),0.0,-sin(GetYaw()*(PI/180)) );
	// else glRotatef(GetPitch(), -cos(GetYaw()*(PI/180)),0.0,sin(GetYaw()*(PI/180)) );

	// if(Camera->GetState() != STATE_FPS)
	// {
	// 	glEnable(GL_TEXTURE_2D);
	// 	glActiveTexture(GL_TEXTURE0);
	// 	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_PLAYER));
	// 	glActiveTexture(GL_TEXTURE1);
	// 	glBindTexture(GL_TEXTURE_2D,Data->GetID(IMG_PLAYER_NMAP));
	// 	glDisable(GL_TEXTURE_2D);
	// 	glActiveTexture(GL_TEXTURE0);

	// 	glEnable(GL_BLEND);
	// 	GLUquadricObj *q = gluNewQuadric();
	// 	gluQuadricTexture(q,true);

	// 	Shader->Activate(PROGRAM_LAVAGLOW);
	// 	Shader->SetUniform(colorMap_name, 0);
	// 	Shader->SetUniform(normalMap_name, 1);
	// 	Shader->SetUniform(invRadius_name, 0.0f);
	// 	if(fade) Shader->SetUniform(alpha_name, Camera->GetDistance()/3.0f);
	// 	else Shader->SetUniform(alpha_name, 1.0f);
	// 	Shader->SetUniform(lava_height_name, Lava->GetHeight());
	// 	Shader->SetUniform(posy_name, GetY()-RADIUS);
	// 	gluSphere(q,RADIUS,16,16);
	// 	Shader->Deactivate();

	// 	gluDeleteQuadric(q);
	// 	glDisable(GL_BLEND);
	// }

	// glPopMatrix();
}

void Player::SetFade(bool b)
{
	fade = b;
}