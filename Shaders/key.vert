#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
 
// varying vec3 lightVec; 
// varying vec3 eyeVec;
// varying vec2 texCoord;
// varying vec3 tangent;

// varying vec4 light_ambient;
// varying vec4 light_diffuse;
// varying vec4 light_specular;
// varying vec4 light_position;
// varying vec4 mat_ambient;
// varying vec4 mat_diffuse;
// varying vec4 mat_specular;
// varying float mat_shininess;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 ourColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

out vec2 TexCoord;
out vec4 oColor;
out vec3 LightingColor; // resulting color from lighting calculations

// uniform vec4 light_ambient;
// uniform vec4 light_diffuse;
// uniform vec4 light_specular;
// uniform vec4 light_position;
// uniform vec4 projection;

void main()
{
    oColor = ourColor;
    TexCoord = aTexCoord;


    // gouraud shading
    // ------------------------
    vec3 Position = vec3(model * vec4(aPos, 1.0));
    vec3 Normal = mat3(transpose(inverse(model))) * aNormal;
    
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse   
    vec3 norm = normalize(Normal);
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
    //gl_PointSize = 10;


    // light_ambient  = vec4( 0.0, 0.0, 0.0, 1.0 );
    // light_diffuse  = vec4( 1.0, 1.0, 1.0, 1.0 );
    // light_specular = vec4( 1.0, 1.0, 1.0, 1.0 );
    // light_position = vec4( 50.0, 50.0, 50.0, 0.0 );

    // mat_ambient     = vec4( 0.7, 0.7, 0.7, 1.0 );
    // mat_diffuse     = vec4( 0.8, 0.8, 0.8, 1.0 );
    // mat_specular    = vec4( 0.3, 0.3, 0.3, 1.0 );
    // mat_shininess   = 100.0;


	// vec3 c1 = cross(aNormal, vec3(0.0, 0.0, 1.0)); 
	// vec3 c2 = cross(aNormal, vec3(0.0, 1.0, 0.0)); 

    // if(length(c1)>length(c2)) 
    // {
    //     tangent = c1;	
    // }
	// else 
    // {
    //     tangent = c2;	
    // }

    // vec3 n = normalize(aNormal);
	// vec3 t = normalize(tangent);
	// vec3 b = cross(n, t);

    // vec3 vVertex = vec3(aPos);
	// vec3 tmpVec = light_position.xyz - vVertex;

    // lightVec.x = dot(tmpVec, t);
	// lightVec.y = dot(tmpVec, b);
	// lightVec.z = dot(tmpVec, n);

    // tmpVec = -vVertex;
	// eyeVec.x = dot(tmpVec, t);
	// eyeVec.y = dot(tmpVec, b);
	// eyeVec.z = dot(tmpVec, n);
}