#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 pos_model;
out vec3 pos_eye;
out vec3 normal_model;
//out vec3 normal_eye;

void main()
{
    pos_model    = vec3(aPos);
    pos_eye      = vec3(projection * view * model * aPos);
    normal_model = normalize(aNormals);
    //normal_eye   = normalize(gl_NormalMatrix*aNormals);

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}