#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <list>
#include <algorithm>
#include <utility>
#include <fstream>
#include <string>
#include <iostream>


#include <glm/glm.hpp>
#include <glm/ext.hpp> 

// TODO: We want to remove glu from this application because it is depreciated. For now we will be using it.
#define GLFW_INCLUDE_GLU
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define BUFFER_OFFSET(a) ((void*)(a))

#define PI 3.14159265358979323846f
