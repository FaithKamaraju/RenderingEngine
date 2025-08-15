#pragma once
#include "core/core.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "OpenGL/Texture.h"
#include "OpenGL/Vertex.h"
#include "OpenGL/VertexArrayObject.h"
#include "OpenGL/Shader.h"


namespace RE {
	class RE_API Model
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
