#pragma once
#include "Object.h"

namespace yk
{
	enum WrapMode
	{
		GL_Repeat = GL_REPEAT,
		GL_Mirrored_Repeat = GL_MIRRORED_REPEAT,
		GL_Clamp_To_Edge = GL_CLAMP_TO_EDGE,
		GL_Clamp_To_Border = GL_CLAMP_TO_BORDER
	};

	enum MipmapFilter
	{
		GL_Linear = GL_LINEAR,
		GL_Nearest_Mipmap_Nearest = GL_NEAREST_MIPMAP_NEAREST,
		GL_Linear_Mipmap_Nearest = GL_LINEAR_MIPMAP_NEAREST,
		GL_Nearest_Mipmap_Linear = GL_NEAREST_MIPMAP_LINEAR,
		GL_Linear_Mipmap_Linear = GL_LINEAR_MIPMAP_LINEAR
	};

	enum class TextureType{ Texture2D = GL_TEXTURE_2D, TextureCube = GL_TEXTURE_CUBE_MAP
	};

	class Texture : public Object
	{
		META_OBJECT
	public:
		Texture(TextureType texType=TextureType::Texture2D) { 
			m_textureType = texType;
		}
		Texture(GLint texID, TextureType textureType=TextureType::Texture2D) : m_texture(texID), m_textureType(textureType){}
		void initTexture2D(
			WrapMode wrap_s = GL_Repeat,
			WrapMode wrap_t = GL_Repeat,
			MipmapFilter min_filter = GL_Linear,
			MipmapFilter mag_filter = GL_Linear)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
		}
		void initCubeMap(
			WrapMode wrap_s = GL_Clamp_To_Edge,
			WrapMode wrap_t = GL_Clamp_To_Edge,
			WrapMode wrap_r = GL_Clamp_To_Edge,
			MipmapFilter min_filter = GL_Linear,
			MipmapFilter mag_filter = GL_Linear)
		{
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, min_filter);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, mag_filter);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrap_s);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrap_t);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, wrap_r);
		}
		void load(STD string path, TextureType textureType = TextureType::Texture2D);
		void loadCube(STD vector<STD string> paths);
		void use(GLuint index) {
			glActiveTexture(index);
			glBindTexture((GLenum)m_textureType, m_texture);
			switch (m_textureType)
			{
			case yk::TextureType::Texture2D:
				initTexture2D();
				break;
			case yk::TextureType::TextureCube:
				initCubeMap();
				break;
			default:
				break;
			}
		}
		GLuint getTextureID() { return m_texture; }
		void setTextureID(GLint texID) { m_texture = texID; }
		void setTextureType(TextureType textureType) { m_textureType = textureType; }
		int width, height, nrChannels;

		static unsigned int loadCubemap(STD vector<std::string> faces);
	private:
		GLuint m_texture;
		TextureType m_textureType;
	};

	
}