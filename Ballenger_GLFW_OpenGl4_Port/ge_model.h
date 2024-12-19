#pragma once

#include "Globals.h"
#include "ge_camera.h"
#include "ge_shader.h"
#include "ge_data.h"

//Model array size
#define NUM_MODELS 3

//Model identifiers
enum {
	MODEL_KEY,
	MODEL_PORTAL,
	MODEL_COLUMN
};

class Model
{
public:
	Model();
	~Model();
	void Load(Shader *Shader, Data *Data);
	void Draw(int model_id);
	void Free();
	unsigned int playerVAO;
	unsigned int indexCount;

private:
	unsigned int modelsVertices[NUM_MODELS]; 
	unsigned int modelsVAO[NUM_MODELS]; 
	unsigned int modelsVBO[NUM_MODELS]; 
	unsigned int modelsEBO[NUM_MODELS]; 
	Shader *shader;
	Data *data;

	void GetDisplayList(char* path, unsigned int vertices_key);
};