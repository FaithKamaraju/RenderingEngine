#include "VertexArrayObject.h"

RE::VertexArrayObject::VertexArrayObject()
{
	GLCall(glGenVertexArrays(1, &this->m_vaoID));
}

void RE::VertexArrayObject::BindVertexBuffer(const Vertex* vertices, size_t verticesCount, GLenum mode)
{
	Bind();
	m_VertexBufferObject.AddDataToBuffer(vertices,verticesCount, mode);
	UnBind();
}

void RE::VertexArrayObject::BindElementBuffer(const unsigned int* indices, size_t indicesCount, GLenum mode)
{
	Bind();
	m_ElementBufferObject.AddDataToBuffer(indices,indicesCount,mode);
	UnBind();
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
