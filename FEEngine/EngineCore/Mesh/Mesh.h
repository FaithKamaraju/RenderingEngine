#pragma once

#include <vector>
#include "EngineCore/EngineCore.h"
#include "Renderer/OpenGL/Vertex.h"

namespace FE {

	
	
	struct FE_API Mesh
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


