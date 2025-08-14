#pragma once
#include "core/core.h"
#include "glad/glad.h"
#include <iosfwd>
#include <string>
#include <vector>

#include "OpenGL/Texture.h"



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

		void setVec2(const char* name,int count, const int* value) const;
		void setVec2(const char* name,int count, const unsigned int* value) const;
		void setVec2(const char* name,int count, const float* value) const;
									  
		void setVec3(const char* name,int count, const int* value) const;
		void setVec3(const char* name,int count, const unsigned int* value) const;
		void setVec3(const char* name,int count, const float* value) const;
									  
		void setVec4(const char* name,int count, const int* value) const;
		void setVec4(const char* name,int count, const unsigned int* value) const;
		void setVec4(const char* name,int count, const float* value) const;

		void setMatrix2fv(const char* name, int count, bool bTranspose, const float* value);
		void setMatrix3fv(const char* name, int count, bool bTranspose, const float* value);
		void setMatrix4fv(const char* name, int count, bool bTranspose, const float* value);

	private:
		ShaderSourceObject parseShaderSource(const char* path);
		unsigned int compileShader(GLenum shaderType, const char* shaderSource);
		void linkShaders();

	};
}


//

