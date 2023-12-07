#pragma once

#include "Globals.h"
#include "ge_shader.h"
#include "ge_image.h"
#include "ge_camera.h"

class Skybox
{
public:
	Skybox();
	~Skybox();
	void Load(Shader *Shader);
	void Draw(Camera *Camera);
    unsigned int LoadCubemap(std::vector<std::string> faces);

private:
	int id_Skybox;
    float aspect;
    GLuint skybox_prog;
    GLuint object_prog;
    GLuint vao;

    GLuint skyboxVAO, skyboxVBO;


    GLuint skyboxTextureID;
    GLuint tex;
    GLint skybox_rotate_loc;

    GLint object_mat_mvp_loc;
    GLint object_mat_mv_loc;

    GLfloat *skyboxVertices;

    Shader *shader;
};