#include "testScene.h"
#include <CamMoveCtrl.h>
#include <CubeMove.h>
#include <AlwaysLootAt.h>

using namespace yk;
using namespace std;

SharedPtr<Mesh> getQuadMesh();
SharedPtr<Mesh> getCubeMesh();

SharedPtr<Scene> getTestScene()
{
	auto scene = STD make_shared<Scene>();
	SceneMgr::setCurrentScene(scene);


    // 正方体
	auto cube = GameObject::create();
	auto renderer = cube->addComponent<MeshRenderer>();
    auto filter = cube->addComponent<MeshFilter>();
    //cube->addComponent<CubeMove>();
    cube->addComponent<CamMoveCtrl>();
	auto shader = make_shared<Shader>("shaders/diffuse.vert", "shaders/diffuse.frag");
	renderer->material = make_shared<Material>(shader);
	auto tx = make_shared<Texture>();
	tx->load("container.jpg");
	renderer->material->mainTexture = tx;

	
	auto camera = GameObject::create();
    camera->transform()->translate(vec3(0, 0, 3));
    camera->transform()->LookAt(cube->transform()->position());
	camera->addComponent<Camera>();
    auto c = camera->addComponent<AlwaysLookAt>();
    c->target = cube->transform();
	//camera->addComponent<CamMoveCtrl>();

	
    auto mesh = getCubeMesh();
	filter->sharedMesh = mesh;
	return scene;
}

SharedPtr<Mesh> getQuadMesh()
{
    auto mesh = make_shared<Mesh>();
    mesh->vertices = vector<vec3>{
        vec3(0.5f, 0.5f, 0.0f),	// 右上角
        vec3(0.5f, -0.5f, 0.0f),// 右下角
        vec3(-0.5f, -0.5f, 0.0f),// 左下角
        vec3(-0.5f, 0.5f, 0.0f)// 左上角
    };
    mesh->uv = vector<vec2>{
        vec2(1, 1),
        vec2(1, 0),
        vec2(0, 0),
        vec2(0, 1)
    };
    mesh->triangles = vector<int>{ 0, 1, 3, 1, 2, 3 };
    mesh->setupMesh();
    return mesh;
}

SharedPtr<Mesh> getCubeMesh() {
	auto mesh = make_shared<Mesh>();
    mesh->vertices = vector<vec3>{
        vec3(-0.5f, -0.5f, -0.5f),
        vec3(0.5f, -0.5f, -0.5f), 
        vec3(0.5f,  0.5f, -0.5f), 
        vec3(0.5f,  0.5f, -0.5f), 
        vec3(-0.5f,  0.5f, -0.5f),
        vec3(-0.5f, -0.5f, -0.5f),

        vec3(-0.5f, -0.5f,  0.5f),
        vec3(0.5f, -0.5f,  0.5f), 
        vec3(0.5f,  0.5f,  0.5f), 
        vec3(0.5f,  0.5f,  0.5f), 
        vec3(-0.5f,  0.5f,  0.5f),
        vec3(-0.5f, -0.5f,  0.5f),

        vec3(-0.5f,  0.5f,  0.5f),
        vec3(-0.5f,  0.5f, -0.5f),
        vec3(-0.5f, -0.5f, -0.5f),
        vec3(-0.5f, -0.5f, -0.5f),
        vec3(-0.5f, -0.5f,  0.5f),
        vec3(-0.5f,  0.5f,  0.5f),

        vec3(0.5f,  0.5f,  0.5f), 
        vec3(0.5f,  0.5f, -0.5f), 
        vec3(0.5f, -0.5f, -0.5f), 
        vec3(0.5f, -0.5f, -0.5f), 
        vec3(0.5f, -0.5f,  0.5f), 
        vec3(0.5f,  0.5f,  0.5f), 

        vec3(-0.5f, -0.5f, -0.5f),
        vec3(0.5f, -0.5f, -0.5f), 
        vec3(0.5f, -0.5f,  0.5f), 
        vec3(0.5f, -0.5f,  0.5f), 
        vec3(-0.5f, -0.5f,  0.5f),
        vec3(-0.5f, -0.5f, -0.5f),

        vec3(-0.5f,  0.5f, -0.5f),
        vec3(0.5f,  0.5f, -0.5f), 
        vec3(0.5f,  0.5f,  0.5f), 
        vec3(0.5f,  0.5f,  0.5f), 
        vec3(-0.5f,  0.5f,  0.5f),
        vec3(-0.5f,  0.5f, -0.5f),
    };

    mesh->uv = vector<vec2>{
        vec2(0.0f, 0.0f),
        vec2(1.0f, 0.0f),
        vec2(1.0f, 1.0f),
        vec2(1.0f, 1.0f),
        vec2(0.0f, 1.0f),
        vec2(0.0f, 0.0f),

        vec2(0.0f, 0.0f),
        vec2(1.0f, 0.0f),
        vec2(1.0f, 1.0f),
        vec2(1.0f, 1.0f),
        vec2(0.0f, 1.0f),
        vec2(0.0f, 0.0f),

        vec2(1.0f, 0.0f),
        vec2(1.0f, 1.0f),
        vec2(0.0f, 1.0f),
        vec2(0.0f, 1.0f),
        vec2(0.0f, 0.0f),
        vec2(1.0f, 0.0f),

        vec2(1.0f, 0.0f),
        vec2(1.0f, 1.0f),
        vec2(0.0f, 1.0f),
        vec2(0.0f, 1.0f),
        vec2(0.0f, 0.0f),
        vec2(1.0f, 0.0f),

        vec2(0.0f, 1.0f),
        vec2(1.0f, 1.0f),
        vec2(1.0f, 0.0f),
        vec2(1.0f, 0.0f),
        vec2(0.0f, 0.0f),
        vec2(0.0f, 1.0f),

        vec2(0.0f, 1.0f),
        vec2(1.0f, 1.0f),
        vec2(1.0f, 0.0f),
        vec2(1.0f, 0.0f),
        vec2(0.0f, 0.0f),
        vec2(0.0f, 1.0f)
    };
    for (int i = 0; i < mesh->vertices.size(); i++)
    {
        mesh->triangles.push_back(i);
    }
    mesh->setupMesh();
    return mesh;
}