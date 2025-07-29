#include "VertexArrayObject.h"

RE::VertexArrayObject::VertexArrayObject()
{
	GLCall(glGenVertexArrays(1, &this->m_vaoID));
}

void RE::VertexArrayObject::BindVertexBuffer(const float* vertices, size_t verticesCount, const VertexAttribute* metadata, int NumOfVertexAttributes, GLenum mode)
{
	m_VertexBufferObject.AddDataToBuffer(vertices,verticesCount,metadata,NumOfVertexAttributes, mode);
}

void RE::VertexArrayObject::BindElementBuffer(const unsigned int* indices, size_t indicesCount, GLenum mode)
{

	m_ElementBufferObject.AddDataToBuffer(indices,indicesCount,mode);

}

void RE::VertexArrayObject::Bind()
{
	GLCall(glBindVertexArray(this->m_vaoID));

}

void RE::VertexArrayObject::UnBind()
{
	GLCall(glBindVertexArray(0));
}

RE::VertexArrayObject::~VertexArrayObject()
{
	GLCall(glDeleteVertexArrays(1, &this->m_vaoID));
}
