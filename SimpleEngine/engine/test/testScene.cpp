#include "testScene.h"
#include <CamMoveCtrl.h>
#include <CubeMove.h>
#include <AlwaysLootAt.h>
#include <LightRotateAround.h>
#include <Light.h>
using namespace yk;
using namespace std;

SharedPtr<Mesh> getQuadMesh();
SharedPtr<Mesh> getCubeMesh();
SharedPtr<GameObject> getLight();
SharedPtr<GameObject> getBox();
SharedPtr<GameObject> getCamera();

SharedPtr<Scene> getTestScene()
{
	auto scene = STD make_shared<Scene>();
	SceneMgr::setCurrentScene(scene);

    // 点光
    auto light = getLight();
    
    // 正方体
    auto box = getBox();
    light->getComponent<LightRotateAround>()->target = box->transform();

	// 相机
    auto camera = getCamera();

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

    mesh->normals = vector<vec3>{
        vec3(0.0f,  0.0f, -1.0f),
        vec3(0.0f,  0.0f, -1.0f),
        vec3(0.0f,  0.0f, -1.0f),
        vec3(0.0f,  0.0f, -1.0f),
        vec3(0.0f,  0.0f, -1.0f),
        vec3(0.0f,  0.0f, -1.0f),

        vec3(0.0f,  0.0f,  1.0f),
        vec3(0.0f,  0.0f,  1.0f),
        vec3(0.0f,  0.0f,  1.0f),
        vec3(0.0f,  0.0f,  1.0f),
        vec3(0.0f,  0.0f,  1.0f),
        vec3(0.0f,  0.0f,  1.0f),

        vec3(-1.0f,  0.0f,  0.0f),
        vec3(-1.0f,  0.0f,  0.0f),
        vec3(-1.0f,  0.0f,  0.0f),
        vec3(-1.0f,  0.0f,  0.0f),
        vec3(-1.0f,  0.0f,  0.0f),
        vec3(-1.0f,  0.0f,  0.0f),

        vec3(1.0f,  0.0f,  0.0f),
        vec3(1.0f,  0.0f,  0.0f),
        vec3(1.0f,  0.0f,  0.0f),
        vec3(1.0f,  0.0f,  0.0f),
        vec3(1.0f,  0.0f,  0.0f),
        vec3(1.0f,  0.0f,  0.0f),

        vec3(0.0f, -1.0f,  0.0f),
        vec3(0.0f, -1.0f,  0.0f),
        vec3(0.0f, -1.0f,  0.0f),
        vec3(0.0f, -1.0f,  0.0f),
        vec3(0.0f, -1.0f,  0.0f),
        vec3(0.0f, -1.0f,  0.0f),

        vec3(0.0f,  1.0f,  0.0f),
        vec3(0.0f,  1.0f,  0.0f),
        vec3(0.0f,  1.0f,  0.0f),
        vec3(0.0f,  1.0f,  0.0f),
        vec3(0.0f,  1.0f,  0.0f),
        vec3(0.0f,  1.0f,  0.0f)
    };

    for (int i = 0; i < mesh->vertices.size(); i++)
    {
        mesh->triangles.push_back(i);
    }
    mesh->setupMesh();
    return mesh;
}

SharedPtr<GameObject> getLight()
{
    auto gb = GameObject::create();
    auto render = gb->addComponent<MeshRenderer>();
    auto filter = gb->addComponent<MeshFilter>();
    gb->addComponent<LightRotateAround>();
    gb->addComponent<Light>();
    render->material = make_shared<Material>(make_shared<Shader>("shaders/diffuse.vert", "shaders/light.frag"));
    filter->sharedMesh = getCubeMesh();
    gb->transform()->translate(vec3(1, 2, -2));
    gb->transform()->scale() *= vec3(0.5, 0.5, 0.5f);
    return gb;
}

SharedPtr<GameObject> getBox()
{
    auto cube = GameObject::create();
    auto renderer = cube->addComponent<MeshRenderer>();
    auto filter = cube->addComponent<MeshFilter>();
    //cube->addComponent<CamMoveCtrl>();
    auto shader = make_shared<Shader>("shaders/diffuse.vert", "shaders/diffuse.frag");
    renderer->material = make_shared<Material>(shader);
    auto tx = make_shared<Texture>();
    tx->load("container.jpg");
    renderer->material->mainTexture = tx;
    auto mesh = getCubeMesh();
    filter->sharedMesh = mesh;
    return cube;
}

SharedPtr<GameObject> getCamera()
{
    auto camera = GameObject::create();
    camera->transform()->translate(vec3(0, 0, 3));
    camera->addComponent<Camera>();
    camera->addComponent<CamMoveCtrl>();
    return camera;
}
