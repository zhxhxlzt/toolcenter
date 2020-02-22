#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"
#include "GraphicDebug.h"
#include "Texture.h"


using namespace std;
using namespace yk;

static unsigned char* loadData(string path, int& width, int& height, int& nrChannels)
{
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	return data;
}


void Texture::load(string path, TextureType textureType)
{
	m_textureType = textureType;
	GLenum target = (GLenum)textureType;
	glBindTexture((GLenum)target, m_texture);
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	unsigned int rgbMode = GL_RGB;
	if (nrChannels == 4)
	{
		rgbMode = GL_RGBA;
	}
	if (data)
	{
		glTexImage2D(target, 0, rgbMode, width, height, 0, rgbMode, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(target);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void Texture::loadCube(vector<string> paths)
{
	glCheckError();
	m_textureType = TextureType::TextureCube;
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	for (int i = 0; i < paths.size(); i++)
	{
		int width, height, nrChannels;
		auto data = loadData(paths[i], width, height, nrChannels);
		unsigned int rgbMode = GL_RGB;
		if (nrChannels == 4)
		{
			rgbMode = GL_RGBA;
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, rgbMode, width, height, 0, rgbMode, GL_UNSIGNED_BYTE, data);
		glCheckError();
		stbi_image_free(data);
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

unsigned int Texture::loadCubemap(STD vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}