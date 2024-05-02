#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 Pos;
in vec3 LightingColor; 

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{    
    //FragColor = texture(texture2, TexCoords);
	FragColor = mix( texture(texture2, TexCoords) , texture(texture1, TexCoords) , Normal.y*Normal.y) * vec4(LightingColor, 1.0) ; //en base a la pendiente
    if(Pos.y <= 10) FragColor = mix( texture(texture2, TexCoords) , FragColor , (Pos.y-4)/6.0 ) * vec4(LightingColor, 1.0) ; //cerca de la lava es roca
}





// #version 330 core
// out vec4 FragColor;

// in vec3 ourColor;
// in vec2 TexCoord;

// // texture samplers
// uniform sampler2D tex_top;
// uniform sampler2D tex_side;

// void main()
// {
// 	// linearly interpolate between both textures (80% container, 20% awesomeface)
// 	FragColor = mix(texture(tex_top, TexCoord), texture(tex_side, TexCoord), 0.2);
// }