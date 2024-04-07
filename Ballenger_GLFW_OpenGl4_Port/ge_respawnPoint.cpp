#include "ge_respawnPoint.h"

RespawnPoint::RespawnPoint(){}
RespawnPoint::~RespawnPoint(){}

//suponiendo matrices 4x4
/*
bool MatrixInverse(GLfloat m[16], GLfloat invOut[16])
{
    double inv[16], det;
    int i;

    inv[0] = m[5]  * m[10] * m[15] - 
             m[5]  * m[11] * m[14] - 
             m[9]  * m[6]  * m[15] + 
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] - 
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] + 
              m[4]  * m[11] * m[14] + 
              m[8]  * m[6]  * m[15] - 
              m[8]  * m[7]  * m[14] - 
              m[12] * m[6]  * m[11] + 
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] - 
             m[4]  * m[11] * m[13] - 
             m[8]  * m[5] * m[15] + 
             m[8]  * m[7] * m[13] + 
             m[12] * m[5] * m[11] - 
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] + 
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] - 
               m[8]  * m[6] * m[13] - 
               m[12] * m[5] * m[10] + 
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] + 
              m[1]  * m[11] * m[14] + 
              m[9]  * m[2] * m[15] - 
              m[9]  * m[3] * m[14] - 
              m[13] * m[2] * m[11] + 
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] - 
             m[0]  * m[11] * m[14] - 
             m[8]  * m[2] * m[15] + 
             m[8]  * m[3] * m[14] + 
             m[12] * m[2] * m[11] - 
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] + 
              m[0]  * m[11] * m[13] + 
              m[8]  * m[1] * m[15] - 
              m[8]  * m[3] * m[13] - 
              m[12] * m[1] * m[11] + 
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] - 
              m[0]  * m[10] * m[13] - 
              m[8]  * m[1] * m[14] + 
              m[8]  * m[2] * m[13] + 
              m[12] * m[1] * m[10] - 
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] - 
             m[1]  * m[7] * m[14] - 
             m[5]  * m[2] * m[15] + 
             m[5]  * m[3] * m[14] + 
             m[13] * m[2] * m[7] - 
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] + 
              m[0]  * m[7] * m[14] + 
              m[4]  * m[2] * m[15] - 
              m[4]  * m[3] * m[14] - 
              m[12] * m[2] * m[7] + 
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] - 
              m[0]  * m[7] * m[13] - 
              m[4]  * m[1] * m[15] + 
              m[4]  * m[3] * m[13] + 
              m[12] * m[1] * m[7] - 
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] + 
               m[0]  * m[6] * m[13] + 
               m[4]  * m[1] * m[14] - 
               m[4]  * m[2] * m[13] - 
               m[12] * m[1] * m[6] + 
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] + 
              m[1] * m[7] * m[10] + 
              m[5] * m[2] * m[11] - 
              m[5] * m[3] * m[10] - 
              m[9] * m[2] * m[7] + 
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] - 
             m[0] * m[7] * m[10] - 
             m[4] * m[2] * m[11] + 
             m[4] * m[3] * m[10] + 
             m[8] * m[2] * m[7] - 
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] + 
               m[0] * m[7] * m[9] + 
               m[4] * m[1] * m[11] - 
               m[4] * m[3] * m[9] - 
               m[8] * m[1] * m[7] + 
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] - 
              m[0] * m[6] * m[9] - 
              m[4] * m[1] * m[10] + 
              m[4] * m[2] * m[9] + 
              m[8] * m[1] * m[6] - 
              m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;

    return true;
}
*/

void RespawnPoint::Draw(int tex_id, bool activated, Shader *shader, Camera *camera)
{
    // char texture1[] = "texture1\0";
	// char texture2[] = "texture2\0";

	// //ang = fmod(ang+LEVITATION_SPEED/20,360);

    // glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    // if(id==0) color = glm::vec4(1.0f,0.0f,0.0f,1.0f); //rojo
	// if(id==1) color = glm::vec4(1.0f,1.0f,0.0f,1.0f); //amarillo
	// if(id==2) color = glm::vec4(0.0f,1.0f,0.0f,1.0f); //verde
	// if(id==3) color = glm::vec4(0.1f,0.1f,1.0f,1.0f); //azul
	// if(id==4) color = glm::vec4(1.0f,0.0f,1.0f,1.0f); //violeta

	// glm::mat4 model = glm::mat4(1.0f);
	// glm::mat4 view =  camera->GetViewMatrix(); // remove translation from the view matrix
	// glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)camera->SCR_WIDTH/(float)camera->SCR_HEIGHT, 0.1f, 1000.0f);

   	// model = glm::translate(model, glm::vec3(x,y+HEIGHT_OFFSET,z));
   	// model = glm::translate(model, glm::vec3(0,0,HEIGHT_OFFSET));
	// model = glm::rotate(model, yaw, glm::vec3(0.0f,1.0f,0.0f));

	// glActiveTexture(GL_TEXTURE0);
	// glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_KEY));
	// glActiveTexture(GL_TEXTURE1);
	// glBindTexture(GL_TEXTURE_2D, data->GetID(IMG_KEY_NMAP));
	// shader->Activate(PROGRAM_KEY);
	// shader->setInt(texture1, 0);
	// shader->setInt(texture2, 0);
	// shader->setVec4("ourColor", color);
	// shader->setMat4("model", model);
	// shader->setMat4("view", view);
	// shader->setMat4("projection", projection);


	// column_model->Draw(MODEL_COLUMN);



	// //GLfloat ViewMatrix[16];
	// //glGetFloatv(GL_MODELVIEW_MATRIX, ViewMatrix); //las ultimas transformaciones fueron las de gluLookAt
	
	// glPushMatrix();

	// glDisable(GL_LIGHTING);
	// glEnable(GL_BLEND);
	// glTranslatef(x,y+HEIGHT_OFFSET,z);

	// //circle
	// glEnable(GL_TEXTURE_2D);
	// glBindTexture(GL_TEXTURE_2D,tex_id);

	// glBegin(GL_QUADS);
	// 	glTexCoord2f(0.0f, 1.0f); glVertex3f( CIRCLE_RADIUS, 0,-CIRCLE_RADIUS);
	// 	glTexCoord2f(1.0f, 1.0f); glVertex3f(-CIRCLE_RADIUS, 0,-CIRCLE_RADIUS);
	// 	glTexCoord2f(1.0f, 0.0f); glVertex3f(-CIRCLE_RADIUS, 0, CIRCLE_RADIUS);
	// 	glTexCoord2f(0.0f, 0.0f); glVertex3f( CIRCLE_RADIUS, 0, CIRCLE_RADIUS);
	// glEnd();

	// glDisable(GL_TEXTURE_2D);

	// //f.circle
	
	// //aura
	// glDepthMask(GL_FALSE); //desactivo la escritura en el zbuffer (me aprovecho del algoritmo del pintor para que todos los triangulos se pinten en el orden que le toca [ssi estan a la vista])
	// glDisable(GL_CULL_FACE);
	// GLUquadricObj *q = gluNewQuadric();
	// glRotatef(-90.0f,1.0f,0.0f,0.0f);
	// if(activated) glColor4f(1.0f,0.4f,0.0f,0.6f);
	// else glColor4f(0.5f,0.5f,1.0f,0.6f);

	// shader->Activate(PROGRAM_SIMPLE_LIGHTBEAM);
	// shader->SetUniform("hmax", AURA_HEIGHT);
	// gluCylinder(q,CIRCLE_RADIUS,CIRCLE_RADIUS,AURA_HEIGHT,16,16);
	// shader->Deactivate();

	// glTranslatef(0,0,HEIGHT_OFFSET);
	// gluDisk(q,0,CIRCLE_RADIUS,16,16);

	// glColor4f(1,1,1,1);
	// gluDeleteQuadric(q);
	// glEnable(GL_CULL_FACE);
	// glDepthMask(GL_TRUE);
	// //f.aura

	// glDisable(GL_BLEND);
	// glEnable(GL_LIGHTING);

	// glPopMatrix();
}

void RespawnPoint::SetPos(float posx, float posy, float posz)
{
	x = posx;
	y = posy;
	z = posz;
}
float RespawnPoint::GetX()
{
    return x;
}
float RespawnPoint::GetY()
{
    return y;
}
float RespawnPoint::GetZ()
{
    return z;
}