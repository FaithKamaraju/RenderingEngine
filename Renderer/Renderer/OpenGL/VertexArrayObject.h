#pragma once
#include "core/core.h"
#include "VertexBufferObject.h"
#include "ElementBufferObject.h"

namespace RE {

	class RE_API VertexArrayObject
	{
	public:
		unsigned int m_vaoID;
		
	private:
		VertexBufferObject m_VertexBufferObject;
		ElementBufferObject m_ElementBufferObject;

	public:
		//const float* vertices, const VertexAttribute* metadata, const unsigned int* indices
		VertexArrayObject();
		void BindVertexBuffer(const float* vertices, size_t verticesCount,
			const VertexAttribute* metadata, int NumOfVertexAttributes, GLenum mode);
		void BindElementBuffer(const unsigned int* indices, size_t indicesCount, GLenum mode);

		void Bind();
		void UnBind();

		~VertexArrayObject();
	private:

	};
}


