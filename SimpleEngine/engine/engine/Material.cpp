#include "Material.h"
#include "Texture.h"
using namespace yk;
using namespace std;

void Material::setShaderTexture(SharedPtr<Shader> targetShader)
{
	targetShader->use();
	if (mainTexture)
	{
		mainTexture->use(GL_TEXTURE0);
		targetShader->set("_MainTex", 0);
	}
		
	int idx = 1;
	for (auto it = m_textures.begin(); it != m_textures.end(); ++it)
	{
		auto& pair = *it;
		auto name = pair.first;
		auto tex = pair.second;
		tex->use(GL_TEXTURE0 + idx);
		targetShader->set(name.c_str(), idx);
		idx += 1;
	}
}

void Material::setTexture(const string name, SharedPtr<Texture> tex)
{
	m_textures[name] = tex;
}