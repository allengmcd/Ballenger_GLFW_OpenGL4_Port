#include "ge_texture.h"

Texture::Texture(void) {}
Texture::~Texture(void){}

bool Texture::Load(const char *filename,int type,int wraps,int wrapt,int magf,int minf,int mipmap)
{
	Image image;
    int w, h, channels;
    unsigned char *img = image.Load(filename, &w, &h, &channels, 0);
    if(img == NULL) {
        printf("Error loading texture\n");
        exit(1);
    }


	GLenum format = 0;
	if (channels == 1)
		format = GL_RED;
	else if (channels == 3)
		format = GL_RGB;
	else if (channels == 4)
		format = GL_RGBA;

	if(img==NULL) return false;

	width  = w;
	height = h;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D,id);

	glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,
				 GL_UNSIGNED_BYTE,img);
	glGenerateMipmap(GL_TEXTURE_2D);


	// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wraps);
	// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wrapt);

	// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,magf);
	// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,minf);
	// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	// glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	return true;
}
int Texture::GetID()
{
	return id;
}
void Texture::GetSize(int *w,int *h)
{
	*w = width;
	*h = height;
}