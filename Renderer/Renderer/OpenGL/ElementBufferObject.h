#pragma once

#include "core/core.h"
#include "glad/glad.h"

namespace RE {
	class RE_API ElementBufferObject
	{
	public:
		unsigned int m_BufferID;

	private:

	public:
		ElementBufferObject();
		void AddDataToBuffer(const unsigned int* indices, size_t indicesCount, GLenum mode);

		~ElementBufferObject();

		void _bindBuffer();
	};
}


