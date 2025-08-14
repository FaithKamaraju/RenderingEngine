#include "Mesh.h"
#include <string>


RE::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices = indices;
    //this->textures = textures;
}


//RE::Mesh::Mesh(std::vector<Vertex> vertices)
//{
//    this->vertices = vertices;
//}

//void RE::Mesh::Draw(Shader& shader)
//{
//    unsigned int diffuseNr = 1;
//    unsigned int specularNr = 1;
//    for (unsigned int i = 0; i < textures.size(); i++)
//    {
//        GLCall(glActiveTexture(GL_TEXTURE0 + i)); // activate proper texture unit before binding
//        // retrieve texture number (the N in diffuse_textureN)
//        std::string number;
//        std::string name = textures[i].type;
//        if (name == "texture_diffuse")
//            number = std::to_string(diffuseNr++);
//        else if (name == "texture_specular")
//            number = std::to_string(specularNr++);
//        shader.UseShaderProgram();
//        shader.setInt(("material." + name + number).c_str(), i);
//        shader.setFloat("material.shininess", 32.0f);
//        GLCall(glBindTexture(GL_TEXTURE_2D, textures[i].id));
//    }
//
//    // draw mesh
//    VAO.Bind();
//    GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
//    VAO.UnBind();
//
//    GLCall(glActiveTexture(GL_TEXTURE0));
//}
//
//
//void RE::Mesh::Draw(bool light)
//{
//    VAO.Bind();
//    glDrawArrays(GL_TRIANGLES, 0, 36);
//    VAO.UnBind();
//}

//void RE::Mesh::setupMesh()
//{
//    VAO.Bind();
//    VAO.BindVertexBuffer(vertices.data(), sizeof(Vertex) * vertices.size(), GL_STATIC_DRAW);
//    VAO.Bind();
//    VAO.BindElementBuffer(indices.data(), indices.size() * sizeof(unsigned int), GL_STATIC_DRAW);
//    VAO.UnBind();
//}
