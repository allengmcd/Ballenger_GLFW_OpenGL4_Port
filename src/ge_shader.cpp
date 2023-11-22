#include "ge_shader.h"

std::string get_file_contents(const char *filename)
{
  std::ifstream ifs(filename);
  std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
  return content;
}

void glcppShaderSource(GLuint shader, std::string const &shader_string)
{
    GLchar const *shader_source = shader_string.c_str();
    GLint const shader_length = shader_string.size();

    glShaderSource(shader, 1, &shader_source, &shader_length);
}

void load_shader(GLuint shaderobject, const char * shadersourcefilename)
{
    glcppShaderSource(shaderobject,get_file_contents(shadersourcefilename));
}

Shader::Shader(void) {}
Shader::~Shader(void){}

void Shader::Load()
{
	GLuint shader;

	char complex[] = "Shaders/complex.vert\0";
	//char explosion[] = "Shaders/explosion.geom\0";
	char lavaglow_frag[] = "Shaders/lavaglow.frag\0";
	char lavaglow_vert[] = "Shaders/lavaglow.vert\0";
	char lightball[] = "Shaders/lightball.frag\0";
	char lightbeam[] = "Shaders/lightbeam.frag\0";
	char normalmap[] = "Shaders/normalmap.frag\0";
	char simple[] = "Shaders/simple.vert\0";
	char terrain_frag[] = "Shaders/terrain.frag\0";
	char terrain_vert[] = "Shaders/terrain.vert\0";
	char skybox_vert[] = "Shaders/skybox.vert\0";
	char skybox_frag[] = "Shaders/skybox.frag\0";
	//char textured[] = "Shaders/textured.frag\0";
	
	int success;
    char infoLog[512];


	programs[PROGRAM_TERRAIN] = glCreateProgram();
		shader = glCreateShader(GL_VERTEX_SHADER);
		load_shader(shader, terrain_vert);
		glCompileShader(shader);
		glAttachShader(programs[PROGRAM_TERRAIN], shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "PROGRAM_TERRAIN" << std::endl;
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		shader = glCreateShader(GL_FRAGMENT_SHADER);
		load_shader(shader, terrain_frag);
		glCompileShader(shader);
		glAttachShader(programs[PROGRAM_TERRAIN], shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "PROGRAM_TERRAIN" << std::endl;
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		glLinkProgram(programs[PROGRAM_TERRAIN]);
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cout << "PROGRAM_TERRAIN" << std::endl;
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
	

	programs[PROGRAM_SIMPLE_LIGHTBEAM] = glCreateProgram();
		shader = glCreateShader(GL_VERTEX_SHADER);
		load_shader(shader,simple);
		glCompileShader(shader);
		glAttachShader(programs[PROGRAM_SIMPLE_LIGHTBEAM], shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "PROGRAM_SIMPLE_LIGHTBEAM" << std::endl;
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		shader = glCreateShader(GL_FRAGMENT_SHADER);
		load_shader(shader,lightbeam);
		glCompileShader(shader);
		glAttachShader(programs[PROGRAM_SIMPLE_LIGHTBEAM], shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "PROGRAM_SIMPLE_LIGHTBEAM" << std::endl;
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		glLinkProgram(programs[PROGRAM_SIMPLE_LIGHTBEAM]);
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cout << "PROGRAM_SIMPLE_LIGHTBEAM" << std::endl;
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }


	programs[PROGRAM_SIMPLE_LIGHTBALL] = glCreateProgram();
		shader = glCreateShader(GL_VERTEX_SHADER);
		load_shader(shader,simple);
		glCompileShader(shader);
		glAttachShader(programs[PROGRAM_SIMPLE_LIGHTBALL], shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "PROGRAM_SIMPLE_LIGHTBALL" << std::endl;
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		shader = glCreateShader(GL_FRAGMENT_SHADER);
		load_shader(shader,lightball);
		glCompileShader(shader);
		glAttachShader(programs[PROGRAM_SIMPLE_LIGHTBALL], shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "PROGRAM_SIMPLE_LIGHTBALL" << std::endl;
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		glLinkProgram(programs[PROGRAM_SIMPLE_LIGHTBALL]);
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cout << "PROGRAM_SIMPLE_LIGHTBALL" << std::endl;
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }


	programs[PROGRAM_LAVAGLOW] = glCreateProgram();
		shader = glCreateShader(GL_VERTEX_SHADER);
		load_shader(shader,lavaglow_vert);
		glCompileShader(shader);
		glAttachShader(programs[PROGRAM_LAVAGLOW], shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "PROGRAM_lavaglow_vert" << std::endl;
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		shader = glCreateShader(GL_FRAGMENT_SHADER);
		load_shader(shader,lavaglow_frag);
		glCompileShader(shader);
		glAttachShader(programs[PROGRAM_LAVAGLOW], shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "PROGRAM_lavaglow_frag" << std::endl;
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		glLinkProgram(programs[PROGRAM_LAVAGLOW]);
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cout << "PROGRAM_LAVAGLOW" << std::endl;
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }


	programs[PROGRAM_COMPLEX_NORMALMAP] = glCreateProgram();
		shader = glCreateShader(GL_VERTEX_SHADER);
		load_shader(shader,complex);
		glCompileShader(shader);
		glAttachShader(programs[PROGRAM_COMPLEX_NORMALMAP], shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "PROGRAM_COMPLEX_NORMALMAP" << std::endl;
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		shader = glCreateShader(GL_FRAGMENT_SHADER);
		load_shader(shader,normalmap);
		glCompileShader(shader);
		glAttachShader(programs[PROGRAM_COMPLEX_NORMALMAP], shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "PROGRAM_COMPLEX_NORMALMAP" << std::endl;
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		glLinkProgram(programs[PROGRAM_COMPLEX_NORMALMAP]);
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cout << "PROGRAM_COMPLEX_NORMALMAP" << std::endl;
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

	programs[PROGRAM_SKYBOX] = glCreateProgram();
		shader = glCreateShader(GL_VERTEX_SHADER);
		load_shader(shader,skybox_vert);
		glCompileShader(shader);
		glAttachShader(programs[PROGRAM_SKYBOX], shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "PROGRAM_SKYBOX" << std::endl;
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		shader = glCreateShader(GL_FRAGMENT_SHADER);
		load_shader(shader,skybox_frag);
		glCompileShader(shader);
		glAttachShader(programs[PROGRAM_SKYBOX], shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "PROGRAM_SKYBOX" << std::endl;
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		glLinkProgram(programs[PROGRAM_SKYBOX]);
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cout << "PROGRAM_SKYBOX" << std::endl;
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
	

	glDeleteShader(shader);
}

void Shader::Activate(int program_id)
{
	glUseProgram(programs[program_id]);
	current_prog_id = program_id;
}

void Shader::Deactivate()
{
	glUseProgram(0);
}