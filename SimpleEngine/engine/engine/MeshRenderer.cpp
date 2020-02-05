#include "MeshRenderer.h"
#include "GameObject.h"
#include "Texture.h"
#include "GraphicDebug.h"
using namespace yk;

void MeshRenderer::rendering()
{
	material->use();
	auto f = gameObject()->getComponent<MeshFilter>();
	auto mesh = f->sharedMesh;
	mesh->draw();
	glCheckError();
}