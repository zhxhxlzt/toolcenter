#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"
#include "Texture.h"

using namespace std;
using namespace yk;

void Texture::load(string path, TextureType textureType)
{
	m_textureType = textureType;
	GLenum target = (GLenum)textureType;
	glBindTexture((GLenum)target, m_texture);
	int width, height, nrChannels;
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