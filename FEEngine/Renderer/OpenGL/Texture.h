#pragma once

#include "EngineCore/EngineCore.h"
#include "Renderer/stb_image.h"
#include <iostream>
#include <string>
#include "glad/glad.h"


namespace FE {


	struct FE_API Texture {
		unsigned int id;
		std::string type;
        std::string path;

        static unsigned int TextureFromFile(const char* path, const std::string& directory)
        {
            stbi_set_flip_vertically_on_load(true);
            std::string filename = std::string(path);
            filename = directory + '/' + filename;

            unsigned int textureID;
            GLCall(glGenTextures(1, &textureID));

            int width, height, nrComponents;
            unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
            if (data)
            {
                GLenum format;
                if (nrComponents == 1)
                    format = GL_RED;
                else if (nrComponents == 3)
                    format = GL_RGB;
                else if (nrComponents == 4)
                    format = GL_RGBA;

                GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
                GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));
                GLCall(glGenerateMipmap(GL_TEXTURE_2D));

                GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
                GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
                GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
                GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

                stbi_image_free(data);
            }
            else
            {
                std::cout << "Texture failed to load at path: " << path << std::endl;
                stbi_image_free(data);
            }

            return textureID;
        }

        static unsigned int TextureFromMemory(const aiTexture* texture)
        {
            stbi_set_flip_vertically_on_load(false);
            unsigned int textureID;
            GLCall(glGenTextures(1, &textureID));

            int width, height, nrComponents;
            unsigned char* data = nullptr;
            if (texture->mHeight == 0)
            {
                 data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(texture->pcData), texture->mWidth, &width, &height, &nrComponents, 0);
            }
            else
            {
                data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(texture->pcData), texture->mWidth * texture->mHeight, &width, &height, &nrComponents, 0);
            }
            if (data)
            {
                GLenum format;
                if (nrComponents == 1)
                    format = GL_RED;
                else if (nrComponents == 3)
                    format = GL_RGB;
                else if (nrComponents == 4)
                    format = GL_RGBA;

                GLCall(glBindTexture(GL_TEXTURE_2D, textureID));
                // Texture specification
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

                //GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));
                GLCall(glGenerateMipmap(GL_TEXTURE_2D));

                GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
                GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
                GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
                GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

                stbi_image_free(data);
            }
            else
            {
                std::cout << "Texture failed to load at path: " << texture->mFilename.C_Str() << std::endl;
                stbi_image_free(data);
            }

            return textureID;
            
        }
	};

    
}
