#pragma once
#include "core.h"
#include "glad/glad.h"
#include "VerticesMetaData.h"

namespace RE {

	class RE_API VertexBufferObject
	{
	public:
		unsigned int m_BufferID;

	private:

	public:

		VertexBufferObject();
		void AddDataToBuffer(const float* vertices, size_t verticesCount,
			const VertexAttribute* metadata, int NumOfVertexAttributes, GLenum mode);
		~VertexBufferObject();

		void _bindBuffer();
		void _addVertexAttribute(unsigned int location, unsigned int size, GLenum type,
			bool bNormalized, unsigned int stride, const void* offset);

	private:

	};


	

}


