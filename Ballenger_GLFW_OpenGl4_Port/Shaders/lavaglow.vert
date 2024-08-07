#version 330 core
layout (location = 0) in vec2 aTexCoords;
layout (location = 1) in vec3 aPos;

out vec2 TexCoords;
out vec3 Pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aTexCoords;    
    Pos = aPos;    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}







// #version 330 core
// layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;
// layout (location = 2) in vec2 aTexCoord;

// out vec3 ourColor;
// out vec2 TexCoord;

// void main()
// {
// 	gl_Position = vec4(aPos, 1.0);
// 	//ourColor = aColor;
// 	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
// }