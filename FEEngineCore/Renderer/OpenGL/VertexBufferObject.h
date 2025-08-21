#pragma once
#include "EngineMacros.h"
#include "glad/glad.h"
#include "Vertex.h"

namespace FE {

	class FE_API VertexBufferObject
	{
	public:
		unsigned int m_BufferID;

	private:

	public:

		VertexBufferObject();
		void AddDataToBuffer(const Vertex* vertices, size_t verticesCount, GLenum mode);
		~VertexBufferObject();

		void _bindBuffer();
		void _unbindBuffer();
	private:

	};


	

}


