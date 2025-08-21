#include "ErrorChecking.h"
#include "glad/glad.h"

#include <iostream>


void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}
bool GLLogError(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << ") " << file << ":" << line << ":" << function << '\n';
		return false;
	}
	return true;
}