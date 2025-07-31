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

		void setBool(const char* name, bool value) const;
		void setInt(const char* name, int value) const;
		void setFloat(const char* name, float value) const;
		void setMatrix4fv(const char* name, size_t count, bool bTranspose, const float* value);

	private:
		ShaderSourceObject parseShaderSource(const char* path);
		unsigned int compileShader(GLenum shaderType, const char* shaderSource);
		void linkShaders();

	};
}


//

