#pragma once
#include "Object.h"
#include "Shader.h"
namespace yk
{
	class Texture;
	class Material : public Object
	{
	public:
		Material(SharedPtr<Shader> shader) : Object(), shader(shader) {}
		SharedPtr<Shader> shader;
		SharedPtr<Texture> mainTexture;
		void setShaderTexture(SharedPtr<Shader> shader);
		void setTexture(string name, SharedPtr<Texture> tex);
	private:
		STD map<const string, SharedPtr<Texture>> m_textures;
	};
}