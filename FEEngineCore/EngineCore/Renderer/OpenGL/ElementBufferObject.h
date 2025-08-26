#pragma once

#include "EngineMacros.h"
#include "glad/glad.h"

namespace FE {
	class FE_API ElementBufferObject
	{
	public:
		unsigned int m_BufferID;

	private:

	public:
		ElementBufferObject();
		void AddDataToBuffer(const unsigned int* indices, size_t indicesCount, GLenum mode);

		~ElementBufferObject();

		void _bindBuffer();
		void _unbindBuffer();
	};
}


