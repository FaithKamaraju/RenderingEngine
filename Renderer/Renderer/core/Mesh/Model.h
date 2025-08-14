#pragma once
#include "core/core.h"
#include <string>
#include <vector>
#include <map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "core/Mesh/Mesh.h"



namespace RE {
	class Shader;
	class RE_API Model
	{
	public:
		
		Model(const char* path);
		void Draw(Shader& shader);

	private:
		std::vector<Texture> textures_loaded;
		std::map<unsigned int, std::vector<Texture>> textures;
		std::map<unsigned int, std::vector<std::shared_ptr<Mesh>>> meshes;
		std::map<unsigned int, size_t> indicesCount;
		std::map<unsigned int, VertexArrayObject> m_VAOs;
		std::string directory;

        void loadModel(std::string path);
        void processNode(aiNode* node, const aiScene* scene);
		void processMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
                    std::string typeName);

		
	};
}
