#pragma once
#include "EngineCore/EngineCore.h"
#include "glad/glad.h"

namespace FE {
	struct FE_API VertexAttribute
	{
		unsigned int location;
		unsigned int size;
		GLenum type; //GL_FLOAT or GL_UNSIGNED_INT
		bool bNormalized; // GL_FALSE OR GL_TRUE
		unsigned int stride;
		const void* offset;
	};

}


