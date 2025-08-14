#include "VertexBufferObject.h"
#include "ElementBufferObject.h"


RE::VertexBufferObject::VertexBufferObject()
{
	GLCall(glGenBuffers(1, &this->m_BufferID));
}

void RE::VertexBufferObject::AddDataToBuffer(const Vertex* vertices, size_t verticesCount, GLenum mode)
{
	_bindBuffer();
	GLCall(glBufferData(GL_ARRAY_BUFFER, verticesCount, vertices, mode));

	// vertex position
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));
	
	// vertex normals
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal)));
	// vertex texture coords
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords)));

}

RE::VertexBufferObject::~VertexBufferObject()
{
	glDeleteBuffers(1, &this->m_BufferID);
}


void RE::VertexBufferObject::_bindBuffer()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->m_BufferID));
}
void RE::VertexBufferObject::_unbindBuffer()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

