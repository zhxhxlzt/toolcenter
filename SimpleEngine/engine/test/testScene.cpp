#include "testScene.h"
#include <CamMoveCtrl.h>
#include <CubeMove.h>
#include <AlwaysLootAt.h>
#include <LightRotateAround.h>
#include <Light.h>

using namespace yk;
using namespace std;

SharedPtr<Mesh> getScreenMesh();
SharedPtr<Mesh> getQuadMesh();
SharedPtr<Mesh> getCubeMesh();
SharedPtr<GameObject> getLight();
SharedPtr<GameObject> getDirectionalLight();
SharedPtr<GameObject> getPointLight();
SharedPtr<GameObject> getPlane();
SharedPtr<GameObject> getBox();
SharedPtr<GameObject> getCubeDebugBox();
SharedPtr<GameObject> getShadowDebug();
SharedPtr<GameObject> getCamera();
SharedPtr<Material> getOutlineMat();

SharedPtr<Scene> getTestScene()
{
	auto scene = STD make_shared<Scene>();
	SceneMgr::setCurrentScene(scene);

    // 平行光
    //auto light = getDirectionalLight();

    auto pointLight = getPointLight();
    pointLight->transform()->translate(vec3(3, 5, 0));


    // debug cube map shadow
    /*auto debugCube = getCubeDebugBox();
    debugCube->transform()->translate(vec3(0, 10, 0));
    debugCube->transform()->scale() *= vec3(5, 5, 5);*/

    // 正方体
    auto box = getBox();
    //box->getComponent<MeshRenderer>()->materials.push_back(getOutlineMat());

    auto box2 = getBox();
    box2->transform()->translate(vec3(3, 0, 1));
    auto m = box2->getComponent<MeshRenderer>();
    m->materials.push_back(getOutlineMat());
    //m->material = getOutlineMat();
    /*auto box2 = getBox();
    auto box3 = getBox();*/
    // 地板
    //auto plane = getPlane();
    //plane->transform()->scale() *= vec3(50, 1, 50);

	// 相机
    auto camera = getCamera();
	return scene;
}

SharedPtr<Mesh> getScreenMesh()
{
    auto mesh = make_shared<Mesh>();
    mesh->vertices = vector<vec3>
    {
        vec3(-1.0f,  1.0f, 0.0f),
        vec3(-1.0f, -1.0f, 0.0f),
        vec3( 1.0f,  1.0f, 0.0f),
        vec3( 1.0f, -1.0f, 0.0f),
    };

    mesh->uv = vector<vec2>{
        vec2(0.0f, 1.0f),
        vec2(0.0f, 0.0f),
        vec2(1.0f, 1.0f),
        vec2(1.0f, 0.0f),
    };
    return mesh;
}

SharedPtr<Mesh> getQuadMesh()
{
    auto mesh = make_shared<Mesh>();
    mesh->vertices = vector<vec3>{
        vec3(0.5f,  0.0f, -0.5f),	// 右上角
        vec3(0.5f,  0.0f,  0.5f),// 右下角
        vec3(-0.5f, 0.0f,  0.5f),// 左下角
        vec3(-0.5f, 0.0f, -0.5f)// 左上角
    };
    mesh->uv = vector<vec2>{
        vec2(1, 1),
        vec2(1, 0),
        vec2(0, 0),
        vec2(0, 1)
    };
    mesh->triangles = vector<int>{ 0, 1, 3, 1, 2, 3 };
    mesh->normals = vector<vec3>{
        vec3(0, 1, 0),
        vec3(0, 1, 0),
        vec3(0, 1, 0),
        vec3(0, 1, 0)
    };
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

SharedPtr<GameObject> getDirectionalLight()
{
    auto gb = GameObject::create();
    auto render = gb->addComponent<MeshRenderer>();
    auto filter = gb->addComponent<MeshFilter>();
    render->material = make_shared<Material>(make_shared<Shader>("shaders/diffuse.vert", "shaders/light.frag"));
    filter->sharedMesh = getCubeMesh();
    gb->transform()->translate(vec3(-2.0f, 4.0f, -1.0f));
    gb->transform()->scale() *= vec3(0.5, 0.5, 0.5f);
    gb->transform()->LookAt(vec3(0, 0, 0));

    auto light = gb->addComponent<Light>();
    light->setLightType(LightType::Directional);
    light->setColor(vec3(1.0f, 1.0f, 1.0f));
    return gb;
}

SharedPtr<GameObject> getPointLight()
{
    auto gb = GameObject::create();
    auto render = gb->addComponent<MeshRenderer>();
    auto filter = gb->addComponent<MeshFilter>();
    render->material = make_shared<Material>(make_shared<Shader>("shaders/light.vert", "shaders/light.frag"));
    filter->sharedMesh = getCubeMesh();
    //gb->transform()->translate(vec3(-2.0f, 4.0f, -1.0f));
    //gb->transform()->scale() *= vec3(0.5, 0.5, 0.5f);
    auto light = gb->addComponent<Light>();
    light->setLightType(LightType::Point);
    light->setColor(vec3(1.0f, 1.0f, 1.0f));
    return gb;
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

SharedPtr<GameObject> getCubeDebugBox()
{
    auto cube = GameObject::create();
    auto renderer = cube->addComponent<MeshRenderer>();
    auto filter = cube->addComponent<MeshFilter>();
    auto shader = make_shared<Shader>("shaders/debugCubemap.vert", "shaders/debugCubemap.frag");
    renderer->castShadow = false;
    renderer->material = make_shared<Material>(shader);
    auto mesh = getCubeMesh();
    filter->sharedMesh = mesh;
    return cube;
}

SharedPtr<GameObject> getPlane()
{
    auto plane = GameObject::create();
    auto renderer = plane->addComponent<MeshRenderer>();
    auto filter = plane->addComponent<MeshFilter>();
    auto shader = make_shared<Shader>("shaders/diffuse.vert", "shaders/diffuse.frag");
    renderer->material = make_shared<Material>(shader);
    auto tx = make_shared<Texture>();
    tx->load("wall.jpg");
    renderer->material->mainTexture = tx;
    auto mesh = getQuadMesh();
    filter->sharedMesh = mesh;
    return plane;
}

SharedPtr<GameObject> getShadowDebug()
{
    auto plane = GameObject::create();
    auto renderer = plane->addComponent<MeshRenderer>();
    auto filter = plane->addComponent<MeshFilter>();
    auto shader = make_shared<Shader>("shaders/screen.vert", "shaders/screen.frag");
    shader->name = "screen shadow";
    renderer->material = make_shared<Material>(shader);
    auto mesh = getScreenMesh();
    filter->sharedMesh = mesh;
    return plane;
}

SharedPtr<GameObject> getCamera()
{
    auto camera = GameObject::create();
    camera->transform()->translate(vec3(0, 0, -3));
    camera->addComponent<Camera>();
    camera->addComponent<CamMoveCtrl>();
    return camera;
}

SharedPtr<Material> getOutlineMat()
{
    auto shader = make_shared<Shader>("shaders/outline.vert", "shaders/outline.frag");
    auto mat = make_shared<Material>(shader);
    mat->renderQueue = 2000;
    return mat;
}
