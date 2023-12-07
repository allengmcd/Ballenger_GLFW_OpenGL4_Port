#pragma once

#include "Globals.h"
#include "ge_shader.h"
#include "ge_data.h"
#include "ge_camera.h"

#define TERRAIN_SIZE    1024
const float MAX_HEIGHT = 64.0f;
const float SCALE_FACTOR = 256.0f / MAX_HEIGHT; //el 256 viene por los bits de profundidad del .raw (en mi caso 8bits -> rango de valores [0,255])

struct Coord {float x,y,z;};
struct Vector {float x,y,z;};
struct Triangle {Vector N; Coord barycenter; Coord vertexs[3];};

class Terrain
{
public:
	Terrain();
	~Terrain();
	void  Load(int level, Shader *shader, Data *data);
	void  Draw(Camera *camera);
	void  DrawNormals();
	float GetHeight(float x,float z);
	std::vector<Vector> GetCollisionNormals(Coord &center, float radius);
	float GetSegmentIntersectionLambda(float x,float y,float z, float vx,float vy,float vz, float dist);

private:
	Shader *shader;
	Data *data;
	GLubyte heightmap[TERRAIN_SIZE * TERRAIN_SIZE];
	GLfloat terrainBuffer[(TERRAIN_SIZE * TERRAIN_SIZE)*(3+3+2)*2]; 
	std::vector<Triangle> triangles;
	int id_Terrain,id_Normals;
    unsigned int terrainVBO, terrainVAO;


	void  ComputeTriangle(std::vector<Coord> &triangle);
	Vector  SetNormalPerVertex(int x,float y,int z);
	float GetVertexHeigh(int x, int z);
	bool  IsColliding(Coord P, float radius, Triangle tri,Coord &center);
	bool  IsColliding(Coord P, Coord Q, Triangle tri,float &lambda);
};

/*
******************************
forma de la maya del terreno:
___________ eje de las x
| /| /|...
|/_|/_|
| /|
|/_|
|.
|.
|.
eje de las z
******************************
*/