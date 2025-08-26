#pragma once
#include "EngineMacros.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "EngineCore/Renderer/OpenGL/Texture.h"
#include "EngineCore/Renderer/OpenGL/Vertex.h"
#include "EngineCore/Renderer/OpenGL/VertexArrayObject.h"
#include "EngineCore/Renderer/OpenGL/Shader.h"


namespace FE {
	class FE_API Model
	{
	public:
		
		Model(const char* path);
		void Draw(Shader& shader);

	private:

		int m_NumMeshes, m_NumMaterials;
		std::set<unsigned int> material_ids;
		std::vector<Texture> textures_loaded;
		std::map<unsigned int, std::vector<Texture>> textures;
		std::map<unsigned int, std::vector<Vertex>> vertices;
		std::map<unsigned int, std::vector <unsigned int>> indices;
		std::map<unsigned int, VertexArrayObject> m_VAOs;
		std::string directory;

        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
		void processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
                    std::string typeName, const aiScene* scene);

		
	};
}
