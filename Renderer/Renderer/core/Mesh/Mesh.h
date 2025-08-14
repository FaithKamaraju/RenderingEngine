#pragma once

#include <vector>

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/core.h"
#include "OpenGL/Shader.h"
#include "OpenGL/VertexArrayObject.h"

namespace RE {

	
	
	struct RE_API Mesh
	{
	public:
		// mesh data
		std::vector<Vertex>       vertices;
		std::vector<unsigned int> indices;
		//std::vector<Texture>      textures;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
		//Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
		//void Draw(Shader& shader);
		//void Draw(bool light);
	};
}


