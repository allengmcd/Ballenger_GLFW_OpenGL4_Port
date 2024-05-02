#version 330 core
out vec4 FragColor;

in vec4 oColor;
in vec2 TexCoord;
in vec3 LightingColor; 

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
   	FragColor = texture(texture1, TexCoord) * texture(texture2, TexCoord) * vec4(LightingColor, 1.0) * oColor;
	//FragColor = texture(texture1, TexCoord) * texture(texture2, TexCoord) * oColor;
	//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}