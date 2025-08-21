#include "Model.h"
#include <iostream>
#include <algorithm>
#include <functional>




FE::Model::Model(const char* path) 
{
	loadModel(path);
	for (auto material : material_ids) {
		
		m_VAOs[material].BindVertexBuffer(vertices[material].data(), vertices[material].size() * sizeof(Vertex), GL_STATIC_DRAW);
		m_VAOs[material].BindElementBuffer(indices[material].data(), indices[material].size() * sizeof(unsigned int), GL_STATIC_DRAW);
		
	}
}

void FE::Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_ValidateDataStructure);


	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << "\n";
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	m_NumMeshes = scene->mNumMeshes;
	m_NumMaterials = scene->mNumMaterials;
	processNode(scene->mRootNode, scene);

	
}
void FE::Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene);
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}
void FE::Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<unsigned int> temp_indices;
	if (mesh->mMaterialIndex >= 0) {

		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			glm::vec3 vertex{ mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z };
			glm::vec3 normal{ mesh->mNormals[i].x,mesh->mNormals[i].y ,mesh->mNormals[i].z };
			glm::vec2 texCoord;
			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				texCoord = { mesh->mTextureCoords[0][i].x ,mesh->mTextureCoords[0][i].y };
			}
			else
			{
				texCoord = glm::vec2(0.0f, 0.0f);
			}

			vertices[mesh->mMaterialIndex].emplace_back(Vertex{vertex, normal, texCoord});
		}
		
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				temp_indices.push_back(face.mIndices[j]);
			
		}
		size_t offset = indices[mesh->mMaterialIndex].size();
		std::transform(temp_indices.begin(), temp_indices.end(),
			temp_indices.begin(), [&offset](int val) { return val + offset; });

		indices[mesh->mMaterialIndex].insert(indices[mesh->mMaterialIndex].end(), temp_indices.begin(), temp_indices.end());
	
		if (!material_ids.contains(mesh->mMaterialIndex))
		{
			material_ids.insert(mesh->mMaterialIndex);

			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			

			

			// diffuse maps
			std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);
			textures[mesh->mMaterialIndex].insert(textures[mesh->mMaterialIndex].end(), diffuseMaps.begin(), diffuseMaps.end());
			// specular maps
			std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", scene);
			textures[mesh->mMaterialIndex].insert(textures[mesh->mMaterialIndex].end(), specularMaps.begin(), specularMaps.end());
		}
		
		
	}

}
std::vector<FE::Texture> FE::Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, const aiScene* scene)
{
	std::vector<Texture> textures;

	//if (mat->GetTextureCount(type) == 0)
	//{
	//	Texture texture;
	//	texture.id = Texture::TextureFromFile("BasicGrey.png", "Resources/Textures");
	//	texture.type = typeName;
	//	texture.path = "Resources/Textures/BasicGrey.png";
	//	textures.push_back(texture);
	//	textures_loaded.push_back(texture); // add to loaded textures
	//	return textures;
	//}

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;

		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				/*textures.push_back(textures_loaded[j]);*/
				skip = true;
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it

			Texture texture;
			if (scene->HasTextures()) {
				unsigned index = (unsigned)strtoul(str.C_Str() + 1, NULL, 10);
				texture.id = Texture::TextureFromMemory(scene->mTextures[index]);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				textures_loaded.push_back(texture);
				break;
			}
			
			texture.id = Texture::TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture); // add to loaded textures
		}
	}
	return textures;

}
void FE::Model::Draw(Shader& shader)
{
	for (auto material : material_ids) 
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		for (unsigned int i = 0; i < textures[material].size(); i++)
		{
		    GLCall(glActiveTexture(GL_TEXTURE0 + i)); // activate proper texture unit before binding
		    // retrieve texture number (the N in diffuse_textureN)
		    std::string number;
		    std::string name = textures[material][i].type;
		    if (name == "texture_diffuse")
		        number = std::to_string(diffuseNr++);
		    else if (name == "texture_specular")
		        number = std::to_string(specularNr++);
		    shader.UseShaderProgram();
		    shader.setInt(("material." + name + number).c_str(), i);
		    shader.setFloat("material.shininess", 16.0f);
		    GLCall(glBindTexture(GL_TEXTURE_2D, textures[material][i].id));
		}
		
		// draw mesh
		m_VAOs[material].Bind();
		GLCall(glDrawElements(GL_TRIANGLES, indices[material].size(), GL_UNSIGNED_INT, 0));
		m_VAOs[material].UnBind();
		
		GLCall(glActiveTexture(GL_TEXTURE0));
	}
}
