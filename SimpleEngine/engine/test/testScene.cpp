#include "testScene.h"
using namespace yk;
using namespace std;

SharedPtr<Scene> getTestScene()
{
	auto scene = STD make_shared<Scene>();
	SceneMgr::setCurrentScene(scene);
	auto gb = GameObject::create();

	auto renderer = gb->addComponent<MeshRenderer>();
	auto shader = make_shared<Shader>("shaders/diffuse.vert", "shaders/diffuse.frag");
	renderer->material = make_shared<Material>(shader);

	auto filter = gb->addComponent<MeshFilter>();
	auto mesh = make_shared<Mesh>();
	mesh->vertices = vector<vec3>{
		vec3(0.5f, 0.5f, 0.0f),	// ÓÒÉÏ½Ç
		vec3(0.5f, -0.5f, 0.0f),// ÓÒÏÂ½Ç
		vec3(-0.5f, -0.5f, 0.0f),// ×óÏÂ½Ç
		vec3(-0.5f, 0.5f, 0.0f)// ×óÉÏ½Ç
	};
	mesh->triangles = vector<int>{ 0, 1, 3, 1, 2, 3 };
	mesh->setupMesh();
	filter->sharedMesh = mesh;
	return scene;
}