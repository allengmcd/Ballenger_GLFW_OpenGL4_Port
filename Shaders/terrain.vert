#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 Pos;
out vec3 LightingColor; // resulting color from lighting calculations

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;


void main()
{
    TexCoords = aTexCoords;    
    Normal = aNormal;    
    Pos = aPos;    



    // gouraud shading
    // ------------------------
    vec3 Position = vec3(model * vec4(aPos, 1.0));
    vec3 lightingNormal = mat3(transpose(inverse(model))) * aNormal;
    
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse   
    vec3 norm = normalize(lightingNormal);
    vec3 lightDir = normalize(lightPos - Position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 1.0; // this is set higher to better show the effect of Gouraud shading 
    vec3 viewDir = normalize(viewPos - Position);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;      

    LightingColor = ambient + diffuse + specular;


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