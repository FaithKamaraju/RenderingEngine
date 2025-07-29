#include "VertexBufferObject.h"
#include "ElementBufferObject.h"


RE::VertexBufferObject::VertexBufferObject()
{
	GLCall(glGenBuffers(1, &this->m_BufferID));
}

void RE::VertexBufferObject::AddDataToBuffer(const float* vertices, size_t verticesCount,
	const VertexAttribute* metadata, int NumOfVertexAttributes, GLenum mode)
{
	_bindBuffer();
	GLCall(glBufferData(GL_ARRAY_BUFFER, verticesCount, vertices, mode));
	for (int i = 0; i < NumOfVertexAttributes; i++) {
		_addVertexAttribute(metadata[i].location, metadata[i].size, metadata[i].type, metadata[i].bNormalized, metadata[i].stride, metadata[i].offset);
		GLCall(glEnableVertexAttribArray(metadata[i].location));
	}

}

RE::VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &this->m_BufferID);
}


void RE::VertexBufferObject::_bindBuffer()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_BufferID));
}

void RE::VertexBufferObject::_addVertexAttribute(unsigned int location, unsigned int size, GLenum type,
	bool bNormalized, unsigned int stride, const void* offset)
{
	GLCall(glVertexAttribPointer(location, size, type, bNormalized, stride, offset));
}