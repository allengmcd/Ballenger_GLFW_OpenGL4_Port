#pragma once

#include "Globals.h"
#include "ge_image.h"

class Texture
{
public:
	Texture(void);
	~Texture(void);

	bool Load(const char *filename,int type = GL_RGBA,int wraps = GL_REPEAT,int wrapt = GL_REPEAT,
			  int magf = GL_LINEAR_MIPMAP_LINEAR,int minf = GL_LINEAR,int mipmap = 0);
	int  GetID();
	void GetSize(int *w,int *h);

private:
	GLuint id;
	int width;
	int height;
};
