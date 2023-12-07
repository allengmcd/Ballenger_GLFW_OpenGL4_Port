#pragma once


class Image
{
public:
	Image();
	~Image();
	
    unsigned char *  Load(char const *filename, int *x, int *y, int *comp, int req_comp);
    void Free(void *retval_from_stbi_load);
};
