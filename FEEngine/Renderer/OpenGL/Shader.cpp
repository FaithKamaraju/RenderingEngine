#include "Shader.h"

#include <malloc.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"



FE::Shader::Shader()
{
	GLCall(this->m_ShaderProgramID = glCreateProgram());
}

FE::Shader::~Shader()
{
	GLCall(glDeleteProgram(this->m_ShaderProgramID));
}

FE::ShaderSourceObject FE::Shader::parseShaderSource(const char* path)
{
	std::ifstream stream(path);

	std::string line;
	std::stringstream ssArray[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#SHADER") != std::string::npos) {
			if (line.find("VERTEX") != std::string::npos) {
				type = ShaderType::VERTEX;
			}
			else if (line.find("FRAGMENT") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		}
		else {
			if(type != ShaderType::NONE)
				ssArray[(int)type] << line << '\n';
		}
	}
	return { ssArray[0].str(),ssArray[1].str() };
}

unsigned int FE::Shader::compileShader(GLenum shaderType,const char* shaderSource)
{
	unsigned int shaderID;
	GLCall(shaderID = glCreateShader(shaderType));
	GLCall(glShaderSource(shaderID, 1, &shaderSource, NULL));
	GLCall(glCompileShader(shaderID));
	int  success;
	GLCall(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		int logLength;
		GLCall(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength));
		char* infoLog = (char*)_malloca(logLength * sizeof(char));
		GLCall(glGetShaderInfoLog(shaderID, logLength, &logLength, infoLog));
		std::cout << "ERROR::SHADER::" << (shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << 
			"::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shaderID;
}

void FE::Shader::linkShaders()
{
	GLCall(glLinkProgram(this->m_ShaderProgramID));
	int success;
	GLCall(glGetProgramiv(this->m_ShaderProgramID, GL_LINK_STATUS, &success));
	if (!success) {

		int logLength;
		GLCall(glGetProgramiv(this->m_ShaderProgramID, GL_INFO_LOG_LENGTH, &logLength));
		char* infoLog = (char*)_malloca(logLength * sizeof(char));
		GLCall(glGetProgramInfoLog(this->m_ShaderProgramID, logLength, &logLength, infoLog));
		std::cout << "ERROR::SHADER::PROGRAM_LINKING_FAILED\n" << infoLog << std::endl;
	}

}

void FE::Shader::AttachShaders(const char* path)
{
	ShaderSourceObject shaderSource = this->parseShaderSource(path);
	//std::cout << shaderSource.vertexSource << '\n';
	//std::cout << shaderSource.fragmentSource << '\n';
	unsigned int vertexShaderID = this->compileShader(GL_VERTEX_SHADER,shaderSource.vertexSource.c_str());

	unsigned int fragmentShaderID = this->compileShader(GL_FRAGMENT_SHADER, shaderSource.fragmentSource.c_str());

	GLCall(glAttachShader(this->m_ShaderProgramID, vertexShaderID));
	GLCall(glAttachShader(this->m_ShaderProgramID, fragmentShaderID));

	this->linkShaders();

	GLCall(glDetachShader(this->m_ShaderProgramID, vertexShaderID));
	GLCall(glDetachShader(this->m_ShaderProgramID, fragmentShaderID));
	GLCall(glDeleteShader(vertexShaderID));
	GLCall(glDeleteShader(fragmentShaderID));

}


void FE::Shader::UseShaderProgram()
{
	GLCall(glUseProgram(this->m_ShaderProgramID));
}

void FE::Shader::setBool(const char* name, bool value) const
{
	GLCall(glUniform1i(glGetUniformLocation(this->m_ShaderProgramID, name), (int)value));
}

void FE::Shader::setInt(const char* name, int value) const
{
	GLCall(glUniform1i(glGetUniformLocation(this->m_ShaderProgramID, name), value));
}

void FE::Shader::setFloat(const char* name, float value) const
{
	GLCall(glUniform1f(glGetUniformLocation(this->m_ShaderProgramID, name), value));
}

void FE::Shader::setVec2(const char* name, int count, const int* value) const
{
	GLCall(glUniform2iv(glGetUniformLocation(this->m_ShaderProgramID, name), count, value));
}

void FE::Shader::setVec2(const char* name, int count, const unsigned int* value) const
{
	GLCall(glUniform2uiv(glGetUniformLocation(this->m_ShaderProgramID, name), count, value));
}

void FE::Shader::setVec2(const char* name, int count, const float* value) const
{
	GLCall(glUniform2fv(glGetUniformLocation(this->m_ShaderProgramID, name), count, value));
}

void FE::Shader::setVec3(const char* name, int count, const int* value) const
{
	GLCall(glUniform3iv(glGetUniformLocation(this->m_ShaderProgramID, name), count, value));
}

void FE::Shader::setVec3(const char* name, int count, const unsigned int* value) const
{
	GLCall(glUniform3uiv(glGetUniformLocation(this->m_ShaderProgramID, name), count, value));
}

void FE::Shader::setVec3(const char* name, int count, const float* value) const
{
	GLCall(glUniform3fv(glGetUniformLocation(this->m_ShaderProgramID, name), count, value));
}

void FE::Shader::setVec4(const char* name, int count, const int* value) const
{
	GLCall(glUniform4iv(glGetUniformLocation(this->m_ShaderProgramID, name), count, value));
}

void FE::Shader::setVec4(const char* name, int count, const unsigned int* value) const
{
	GLCall(glUniform4uiv(glGetUniformLocation(this->m_ShaderProgramID, name), count, value));
}

void FE::Shader::setVec4(const char* name, int count, const float* value) const
{
	GLCall(glUniform4fv(glGetUniformLocation(this->m_ShaderProgramID, name), count, value));
}

void FE::Shader::setMatrix2fv(const char* name, int count, bool bTranspose, const float* value)
{
	GLCall(glUniformMatrix2fv(glGetUniformLocation(this->m_ShaderProgramID, name), count, bTranspose, value));
}

void FE::Shader::setMatrix3fv(const char* name, int count, bool bTranspose, const float* value)
{
	GLCall(glUniformMatrix3fv(glGetUniformLocation(this->m_ShaderProgramID, name), count, bTranspose, value));
}

void FE::Shader::setMatrix4fv(const char* name, int count ,bool bTranspose ,const float* value)
{
	GLCall(glUniformMatrix4fv(glGetUniformLocation(this->m_ShaderProgramID, name), count, bTranspose, value));
}




