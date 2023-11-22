#include "ge_image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Image::Image(){}
Image::~Image(){}
	
unsigned char * Image::Load(char const *filename, int *x, int *y, int *comp, int req_comp)
{
	return stbi_load(filename, x, y, comp, req_comp);
}

void Image::Free(void *retval_from_stbi_load)
{
	stbi_image_free(retval_from_stbi_load);
}
