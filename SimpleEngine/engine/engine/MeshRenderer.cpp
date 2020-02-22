#include "MeshRenderer.h"
#include "GameObject.h"
#include "Texture.h"
#include "GraphicDebug.h"
using namespace yk;

void MeshRenderer::rendering(SharedPtr<Shader> shader)
{
	glStencilMask(0xff);
	glStencilFunc(GL_ALWAYS, 1, 0xff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	auto f = gameObject()->getComponent<MeshFilter>();
	auto mesh = f->sharedMesh;
	if (material)
	{
		if (shader == nullptr)
			shader = material->shader;
		material->setShaderTexture(shader);
		shader->set("model", transform()->Model());
		mesh->draw();
	}
	

	// Ä£¿é²âÊÔ
	/*glDisable(GL_DEPTH_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xff);*/
	for (auto m : materials)
	{
		auto shader = m->shader;
		shader->use();
		shader->set("model", transform()->Model());
		mesh->draw();
	}
	/*glStencilFunc(GL_ALWAYS, 1, 0xff);
	glEnable(GL_DEPTH_TEST);*/
}