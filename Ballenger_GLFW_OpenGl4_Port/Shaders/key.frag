#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform vec4 color_dye;

void main()
{
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);// * color_dye;
}