#include "Scene.h"
#include "GameObject.h"
using namespace yk;

RendererList Scene::getRenderers() {
	RendererList renderers;
	for (auto& obj : m_rootGameObjects)
	{
		auto obj_comps = obj->getComponents<Renderer>();
		auto obj_child_comps = obj->getComponentsInChildren<Renderer>();
		renderers.insert(renderers.end(), obj_comps.begin(), obj_comps.end());
		renderers.insert(renderers.end(), obj_child_comps.begin(), obj_child_comps.end());
	}
	return renderers;
}