#pragma once
#include "core.h"
#include "glad/glad.h"
#include <iosfwd>
#include <string>
#include <vector>



namespace RE {
	
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	struct ShaderSourceObject {
		std::string vertexSource;
		std::string fragmentSource;
	};

	class RE_API Shader
	{
	public:
		unsigned int m_ShaderProgramID;
		
	private:

	public:
		Shader();
		~Shader();

		
		void AttachShaders(const char* path);
		void UseShaderProgram();

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;

	private:
		ShaderSourceObject parseShaderSource(const char* path);
		unsigned int compileShader(GLenum shaderType, const char* shaderSource);
		void linkShaders();

	};
}


//

