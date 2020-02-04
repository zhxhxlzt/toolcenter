#include "MeshRenderer.h"
#include "GameObject.h"
using namespace yk;

void MeshRenderer::rendering()
{
	auto f = gameObject()->getComponent<MeshFilter>();
	auto mesh = f->sharedMesh;
	auto shader = material->shader;
	shader->use();
	mesh->draw();
}