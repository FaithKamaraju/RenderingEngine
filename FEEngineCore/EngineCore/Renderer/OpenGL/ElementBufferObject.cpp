#include "ElementBufferObject.h"


FE::ElementBufferObject::ElementBufferObject()
{
	GLCall(glGenBuffers(1, &this->m_BufferID));
}

FE::ElementBufferObject::~ElementBufferObject()
{
	glDeleteBuffers(1, &this->m_BufferID);
}

void FE::ElementBufferObject::AddDataToBuffer(const unsigned int* indices, size_t indicesCount, GLenum mode)
{
	_bindBuffer();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount, indices, mode));
}



void FE::ElementBufferObject::_bindBuffer()
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_BufferID));
}
void FE::ElementBufferObject::_unbindBuffer()
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
