#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexCoord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 bColor;

out vec4 oColor;

//out vec2 TexCoord;

void main()
{
    oColor = bColor;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}