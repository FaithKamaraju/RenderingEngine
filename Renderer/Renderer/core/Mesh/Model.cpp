#include "Model.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include "OpenGL/Shader.h"



RE::Model::Model(const char* path) 
{
	loadModel(path);
	for (auto materialIndex : meshes) {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		for (auto mesh : materialIndex.second)
		{
			vertices.insert(vertices.end(),mesh->vertices.begin(), mesh->vertices.end());
			std::transform(mesh->indices.begin(), mesh->indices.end(),
				mesh->indices.begin(), [&indices](int val) { return val + indices.size(); });
			indices.insert(indices.end(),mesh->indices.begin(), mesh->indices.end());
		}
		indicesCount[materialIndex.first] = indices.size();
		m_VAOs[materialIndex.first].BindVertexBuffer(vertices.data(), vertices.size() * sizeof(Vertex), GL_STATIC_DRAW);
		m_VAOs[materialIndex.first].BindElementBuffer(indices.data(), indices.size() * sizeof(unsigned int), GL_STATIC_DRAW);
		
	}
}

void RE::Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);


	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << "\n";
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}
void RE::Model::processNode(aiNode* node, const aiScene* scene)
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
void RE::Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		glm::vec3 vertex{ mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z};
		glm::vec3 normal{ mesh->mNormals[i].x,mesh->mNormals[i].y ,mesh->mNormals[i].z };
		glm::vec2 texCoord;
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			texCoord = {mesh->mTextureCoords[0][i].x ,mesh->mTextureCoords[0][i].y};
		}
		else
		{
			texCoord = glm::vec2(0.0f, 0.0f);
		}
			
		vertices.push_back(Vertex{ vertex, normal, texCoord });
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0) {
	
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// diffuse maps
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures[mesh->mMaterialIndex].insert(textures[mesh->mMaterialIndex].end(), diffuseMaps.begin(), diffuseMaps.end());
		// specular maps
		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures[mesh->mMaterialIndex].insert(textures[mesh->mMaterialIndex].end(), specularMaps.begin(), specularMaps.end());
	}

	auto finalmesh = std::make_shared<Mesh>( vertices, indices);
	meshes[mesh->mMaterialIndex].push_back(finalmesh);

}
std::vector<RE::Texture> RE::Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
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
			texture.id = Texture::TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture); // add to loaded textures
		}
	}
	return textures;

}
void RE::Model::Draw(Shader& shader)
{
	for (auto &vao : m_VAOs) 
	{
		unsigned int diffuseNr = 1;
		    unsigned int specularNr = 1;
		    for (unsigned int i = 0; i < textures[vao.first].size(); i++)
		    {
		        GLCall(glActiveTexture(GL_TEXTURE0 + i)); // activate proper texture unit before binding
		        // retrieve texture number (the N in diffuse_textureN)
		        std::string number;
		        std::string name = textures[vao.first][i].type;
		        if (name == "texture_diffuse")
		            number = std::to_string(diffuseNr++);
		        else if (name == "texture_specular")
		            number = std::to_string(specularNr++);
		        shader.UseShaderProgram();
		        shader.setInt(("material." + name + number).c_str(), i);
		        shader.setFloat("material.shininess", 32.0f);
		        GLCall(glBindTexture(GL_TEXTURE_2D, textures[vao.first][i].id));
		    }
		
		    // draw mesh
		    vao.second.Bind();
		    GLCall(glDrawElements(GL_TRIANGLES, indicesCount[vao.first], GL_UNSIGNED_INT, 0));
		    vao.second.UnBind();
		
		    GLCall(glActiveTexture(GL_TEXTURE0));
	}
}
