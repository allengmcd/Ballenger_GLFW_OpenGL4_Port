#pragma once

#include "Globals.h"
#include "ge_camera.h"
#include "ge_data.h"
#include "ge_shader.h"

#define BEACON_MIN_RADIUS 0.75f
#define BEACON_HEIGHT 140.0f

class EnergyBeacon
{
public:
	EnergyBeacon();
	~EnergyBeacon();
	void Load(unsigned int sectorCount, unsigned int radius);
	void Draw(Data *data, Camera *camera,Shader *shader);	
	float GetX();
	float GetY();
	float GetZ();
	float GetYaw();
	void SetEnergyBeacon(float posx, float posy, float posz, float ang);
	unsigned int beaconVAO;
	unsigned int indexCount;

private:
	Shader *shader;
	Data *data;

	 // memeber vars
    float baseRadius;
    float topRadius;
    float height;
    int sectorCount;                        // # of slices
    int stackCount;                         // # of stacks
    unsigned int baseIndex;                 // starting index of base
    unsigned int topIndex;                  // starting index of top
    bool smooth;                            // smooth(true) or flat(false)
    int upAxis;                             // X=1, Y=2, Z=3(default)
	float x,y,z;
	float yaw;

    std::vector<float> unitCircleVertices;
    // std::vector<unsigned int> indices;
    // std::vector<unsigned int> lineIndices;

    // interleaved
    std::vector<float> interleavedVertices;
    int interleavedStride;                  // # of bytes to hop to the next vertex (should be 32 bytes)
};