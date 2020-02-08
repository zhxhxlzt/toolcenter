#include "MeshRenderer.h"
#include "GameObject.h"
#include "Texture.h"
#include "GraphicDebug.h"
using namespace yk;

void MeshRenderer::rendering(SharedPtr<Shader> shader)
{
	if (shader == nullptr)
		shader = material->shader;
	material->setShaderTexture(shader);
	shader->set("model", transform()->Model());
	shader->set("lightPos", vec3(1, 2, -2.0f));
	shader->set("lightColor", vec3(1, 1, 1.0f));
	auto f = gameObject()->getComponent<MeshFilter>();
	auto mesh = f->sharedMesh;
	mesh->draw();
	glCheckError();
}