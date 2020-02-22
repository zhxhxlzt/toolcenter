#include "testScene.h"
#include <CamMoveCtrl.h>
#include <CubeMove.h>
#include <AlwaysLootAt.h>
#include <LightRotateAround.h>
#include <Light.h>
#include <SkyBox.h>
#include <Texture.h>
#include <CtrlBoom.h>

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
SharedPtr<GameObject> getExploreBox();
SharedPtr<GameObject> getCubeDebugBox();
SharedPtr<GameObject> getShadowDebug();
SharedPtr<GameObject> getCamera();
SharedPtr<Material> getOutlineMat();
SharedPtr<GameObject> getWindow();
SharedPtr<GameObject> getSkyBox();
SharedPtr<Material> getDebugNormalMat();

SharedPtr<Scene> getTestScene()
{
	auto scene = STD make_shared<Scene>();
	SceneMgr::setCurrentScene(scene);

    auto skyBox = getSkyBox();

    // 平行光
    //auto light = getDirectionalLight();

    // 地板
    //auto plane = getPlane();
    //plane->transform()->scale() *= vec3(50, 1, 50);

    auto pointLight = getPointLight();
    pointLight->transform()->translate(vec3(3, 5, 0));


    // debug cube map shadow
    /*auto debugCube = getCubeDebugBox();
    debugCube->transform()->translate(vec3(0, 10, 0));
    debugCube->transform()->scale() *= vec3(5, 5, 5);*/

    // 正方体
    auto box = getBox();
    auto render = box->getComponent<Renderer>();
    auto debugNormMat = getDebugNormalMat();
    render->materials.push_back(debugNormMat);

    auto exBox = getExploreBox();
    exBox->transform()->translate(vec3(3, 0, 0));

    //box->getComponent<MeshRenderer>()->materials.push_back(getOutlineMat());

    /*auto box2 = getBox();
    box2->transform()->translate(vec3(3, 0, 1));
    auto m = box2->getComponent<MeshRenderer>();
    m->materials.push_back(getOutlineMat());

    auto wnd = getWindow();
    wnd->transform()->translate(vec3(2, 0, -2));

    auto wnd2 = getWindow();
    wnd2->transform()->translate(vec3(2.2, 0, -2));
    wnd2->transform()->rotate(-30, vec3(0, 1, 0));

    auto wnd1 = getWindow();
    wnd1->transform()->translate(vec3(1.8, 0, -3));*/

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
    mesh->triangles = vector<int>{ 0, 3, 1, 1, 3, 2 };
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

        vec3(-0.5f,  -0.5f,  -0.5f),
        vec3(-0.5f, 0.5f, -0.5f),
        vec3(-0.5f,  0.5f, 0.5f),
        
        vec3(-0.5f,  0.5f, 0.5f),
        vec3(-0.5f,  -0.5f,  0.5f),
        vec3(-0.5f, -0.5f,  -0.5f),

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
SharedPtr<GameObject> getExploreBox()
{
    auto cube = GameObject::create();
    auto renderer = cube->addComponent<MeshRenderer>();
    auto filter = cube->addComponent<MeshFilter>();
    auto shader = make_shared<Shader>("shaders/vanish.vert", "shaders/vanish.frag", "shaders/vanish.geom");
    shader->name = "explosion shader";
    renderer->material = make_shared<Material>(shader);
    auto tx = make_shared<Texture>();
    tx->load("container.jpg");
    renderer->material->mainTexture = tx;
    auto mesh = getCubeMesh();
    filter->sharedMesh = mesh;

    auto boom = cube->addComponent<CtrlBoom>();
    boom->distance = 1;
    return cube;
}

static SharedPtr<Mesh> getSkyBoxMesh()
{
    auto mesh = make_shared<Mesh>();
    mesh->vertices = vector<vec3>{
        vec3(-0.5f, -0.5f,  0.5f),  // +z
        vec3(0.5f, -0.5f,  0.5f),
        vec3(0.5f,  0.5f,  0.5f),
        vec3(0.5f,  0.5f,  0.5f),
        vec3(-0.5f,  0.5f,  0.5f),
        vec3(-0.5f, -0.5f,  0.5f),

        vec3(0.5f, -0.5f, -0.5f),  // -z
        vec3(-0.5f, -0.5f, -0.5f),
        vec3(-0.5f,  0.5f, -0.5f),
        vec3(-0.5f,  0.5f, -0.5f),
        vec3(0.5f,  0.5f, -0.5f),
        vec3(0.5f, -0.5f, -0.5f),

        vec3(-0.5f,  0.5f,  0.5f),  // +y
        vec3(0.5f,  0.5f,  0.5f),
        vec3(0.5f,  0.5f, -0.5f),
        vec3(0.5f,  0.5f, -0.5f),
        vec3(-0.5f,  0.5f, -0.5f),
        vec3(-0.5f,  0.5f,  0.5f),

        vec3(-0.5f, -0.5f, -0.5f),  // -y
        vec3(0.5f, -0.5f, -0.5f),
        vec3(0.5f, -0.5f,  0.5f),
        vec3(0.5f, -0.5f,  0.5f),
        vec3(-0.5f, -0.5f, -0.5f),
        vec3(-0.5f, -0.5f,  0.5f),

        vec3(0.5f, -0.5f,  0.5f),  // +x
        vec3(0.5f, -0.5f, -0.5f),
        vec3(0.5f,  0.5f, -0.5f),
        vec3(0.5f,  0.5f, -0.5f),
        vec3(0.5f,  0.5f,  0.5f),
        vec3(0.5f, -0.5f,  0.5f),

        vec3(-0.5f, -0.5f, -0.5f),  // -x
        vec3(-0.5f, -0.5f,  0.5f),
        vec3(-0.5f,  0.5f,  0.5f),
        vec3(-0.5f,  0.5f,  0.5f),
        vec3(-0.5f,  0.5f, -0.5f),
        vec3(-0.5f, -0.5f, -0.5f),
    };
    for (int i = 0; i < mesh->vertices.size(); i++)
    {
        mesh->triangles.push_back(i);
    }
    mesh->setupMesh();
    return mesh;
}

SharedPtr<GameObject> getSkyBox()
{
    glCheckError();

    auto cube = GameObject::create();
    auto filter = cube->addComponent<MeshFilter>();
    auto mesh = getSkyBoxMesh();
    filter->sharedMesh = mesh;
    glCheckError();
    auto skyBoxComp = cube->addComponent<SkyBox>();
    glCheckError();
    auto shader = make_shared<Shader>("shaders/skybox.vert", "shaders/skybox.frag");
    glCheckError();
    glCheckError();
    auto material = make_shared<Material>(shader);
    auto t = make_shared<Texture>(TextureType::TextureCube);
    t->initCubeMap();
    t->loadCube(vector<string>{"skybox/right.jpg", "skybox/left.jpg", "skybox/top.jpg", "skybox/bottom.jpg", "skybox/front.jpg", "skybox/back.jpg"});
    //auto id = Texture::loadCubemap(vector<string>{"skybox/right.jpg", "skybox/left.jpg", "skybox/top.jpg", "skybox/bottom.jpg", "skybox/front.jpg", "skybox/back.jpg"});
    //t->setTextureID(id);
    
    material->setTexture("_SkyBoxA", t);
    auto t0 = make_shared<Texture>();
    t0->load("skybox/right.jpg");
    material->mainTexture = t0;
    skyBoxComp->material = material;
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
    plane->transform()->rotate(180, vec3(1, 0, 0));
    plane->transform()->translate(vec3(0, -0.6, 0));
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

SharedPtr<GameObject> getWindow()
{
    auto window = GameObject::create();
    auto renderer = window->addComponent<MeshRenderer>();
    auto filter = window->addComponent<MeshFilter>();
    auto shader = make_shared<Shader>("shaders/diffuse.vert", "shaders/diffuse.frag");
    renderer->material = make_shared<Material>(shader);
    auto tx = make_shared<Texture>();
    tx->load("blending_transparent_window.png");
    renderer->material->mainTexture = tx;
    auto mesh = getQuadMesh();
    filter->sharedMesh = mesh;
    window->transform()->rotate(90, vec3(1, 0, 0));
    return window;
}

SharedPtr<Material> getDebugNormalMat()
{
    auto shader = make_shared<Shader>("shaders/debugNormal.vert", "shaders/debugNormal.frag", "shaders/debugNormal.geom");
    auto mat = make_shared<Material>(shader);
    return move(mat);
}