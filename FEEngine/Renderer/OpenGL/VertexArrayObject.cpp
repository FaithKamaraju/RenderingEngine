#include "VertexArrayObject.h"

FE::VertexArrayObject::VertexArrayObject()
{
	GLCall(glGenVertexArrays(1, &this->m_vaoID));
}

void FE::VertexArrayObject::BindVertexBuffer(const Vertex* vertices, size_t verticesCount, GLenum mode)
{
	Bind();
	m_VertexBufferObject.AddDataToBuffer(vertices,verticesCount, mode);
	UnBind();
}

void FE::VertexArrayObject::BindElementBuffer(const unsigned int* indices, size_t indicesCount, GLenum mode)
{
	Bind();
	m_ElementBufferObject.AddDataToBuffer(indices,indicesCount,mode);
	UnBind();
}

void FE::VertexArrayObject::Bind()
{
	GLCall(glBindVertexArray(this->m_vaoID));

}

void FE::VertexArrayObject::UnBind()
{
	GLCall(glBindVertexArray(0));
}

FE::VertexArrayObject::~VertexArrayObject()
{
	GLCall(glDeleteVertexArrays(1, &this->m_vaoID));
}
