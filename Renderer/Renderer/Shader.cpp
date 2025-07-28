#include "Shader.h"

#include <malloc.h>
#include <fstream>
#include <iostream>
#include <sstream>


RE::Shader::Shader()
{
	this->m_ShaderProgramID = glCreateProgram();
}

RE::Shader::~Shader()
{
	glDeleteProgram(this->m_ShaderProgramID);
}

RE::ShaderSourceObject RE::Shader::parseShaderSource(const char* path)
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
			ssArray[(int)type] << line << '\n';
		}
	}
	return { ssArray[0].str(),ssArray[1].str() };
}

unsigned int RE::Shader::compileShader(GLenum shaderType,const char* shaderSource)
{
	unsigned int shaderID;
	shaderID = glCreateShader(shaderType); 
	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);
	int  success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int logLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		char* infoLog = (char*)_malloca(logLength * sizeof(char));
		glGetShaderInfoLog(shaderID, logLength, &logLength, infoLog);
		std::cout << "ERROR::SHADER::" << (shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << 
			"::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shaderID;
}

void RE::Shader::linkShaders()
{
	glLinkProgram(this->m_ShaderProgramID);
	int success;
	glGetProgramiv(this->m_ShaderProgramID, GL_LINK_STATUS, &success);
	if (!success) {

		int logLength;
		glGetProgramiv(this->m_ShaderProgramID, GL_INFO_LOG_LENGTH, &logLength);
		char* infoLog = (char*)_malloca(logLength * sizeof(char));
		glGetProgramInfoLog(this->m_ShaderProgramID, logLength, &logLength, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM_LINKING_FAILED\n" << infoLog << std::endl;
	}

}

void RE::Shader::AttachShaders(const char* path)
{
	ShaderSourceObject shaderSource = this->parseShaderSource(path);
	std::cout << shaderSource.vertexSource << '\n';
	std::cout << shaderSource.fragmentSource << '\n';
	unsigned int vertexShaderID = this->compileShader(GL_VERTEX_SHADER,shaderSource.vertexSource.c_str());

	unsigned int fragmentShaderID = this->compileShader(GL_FRAGMENT_SHADER, shaderSource.fragmentSource.c_str());

	glAttachShader(this->m_ShaderProgramID, vertexShaderID);
	glAttachShader(this->m_ShaderProgramID, fragmentShaderID);

	this->linkShaders();

	glDetachShader(this->m_ShaderProgramID, vertexShaderID);
	glDetachShader(this->m_ShaderProgramID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

}


void RE::Shader::UseShaderProgram()
{
	glUseProgram(this->m_ShaderProgramID);
}




