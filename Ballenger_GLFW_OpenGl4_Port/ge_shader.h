#pragma once

#include "Globals.h"


//Program array size
#define NUM_PROGRAMS 9

//Program identifiers
enum {
	PROGRAM_TERRAIN,
	PROGRAM_SIMPLE_LIGHTBEAM,
	PROGRAM_SIMPLE_LIGHTBALL,
	PROGRAM_LAVAGLOW,
	PROGRAM_COMPLEX_NORMALMAP,
	PROGRAM_SKYBOX,
    PROGRAM_PLAYER,
    PROGRAM_KEY,
    PROGRAM_RESPAWNPOINT
};

class Shader
{
public:
	Shader();
	~Shader();

	void Load();
	void Activate(int program_id);
	void Deactivate();

	template <class T>
	void SetUniform(char* uniform, T value)
	{
		GLint loc = glGetUniformLocation(programs[current_prog_id], uniform);
		if (loc != -1)
		{
			if(typeid(T) == typeid(int)) glUniform1i(loc, value);
			else glUniform1f(loc, value);
		}
	}
	void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(programs[current_prog_id], name.c_str()), (int)value); 
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(programs[current_prog_id], name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(programs[current_prog_id], name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const
    { 
        glUniform2fv(glGetUniformLocation(programs[current_prog_id], name.c_str()), 1, &value[0]); 
    }
    void setVec2(const std::string &name, float x, float y) const
    { 
        glUniform2f(glGetUniformLocation(programs[current_prog_id], name.c_str()), x, y); 
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(programs[current_prog_id], name.c_str()), 1, &value[0]); 
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    { 
        glUniform3f(glGetUniformLocation(programs[current_prog_id], name.c_str()), x, y, z); 
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(programs[current_prog_id], name.c_str()), 1, &value[0]); 
    }
    void setVec4(const std::string &name, float x, float y, float z, float w) 
    { 
        glUniform4f(glGetUniformLocation(programs[current_prog_id], name.c_str()), x, y, z, w); 
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(programs[current_prog_id], name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(programs[current_prog_id], name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(programs[current_prog_id], name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
	GLint GetLocation(char* uniform){ return glGetUniformLocation(programs[current_prog_id], uniform);}

private:
	GLuint programs[NUM_PROGRAMS];
	int current_prog_id;
};
