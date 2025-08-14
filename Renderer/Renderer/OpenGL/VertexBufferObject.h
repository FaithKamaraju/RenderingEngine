#pragma once
#include "core/core.h"
#include "glad/glad.h"
#include "OpenGL/Vertex.h"
#include "VerticesMetaData.h"

namespace RE {

	class RE_API VertexBufferObject
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


