#version 330 core
out vec4 FragColor;

in vec2 TexCoord;


void main()
{
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	//FragColor = texture(texture1, TexCoord) * texture(texture2, TexCoord);
}