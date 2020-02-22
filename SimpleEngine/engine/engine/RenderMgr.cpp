#include "RenderMgr.h"
#include "Camera.h"
#include "Transform.h"
#include "Light.h"
#include "Texture.h"
#include "GraphicDebug.h"
#include "GameObject.h"
#include "SkyBox.h"
#include "Mesh.h"
#include "MeshFilter.h"
using namespace yk;

SharedPtr<Window> RenderMgr::s_window = nullptr;
unsigned int RenderMgr::s_matricesBlock = -1;
unsigned int RenderMgr::s_pointLightsBlock = -1;
unsigned int RenderMgr::s_directLightsBlock = -1;
unsigned int RenderMgr::s_lightSpaceMatrixBlock = -1;
SharedPtr<Shader> RenderMgr::s_shadowShader = nullptr;

static SharedPtr<Mesh> getBoxMesh()
{
    auto mesh = make_shared<Mesh>();
    mesh->vertices = vector<vec3>{
        vec3(-0.5f, -0.5f,  0.5f),  // +z
        vec3( 0.5f, -0.5f,  0.5f),
        vec3( 0.5f,  0.5f,  0.5f),
        vec3( 0.5f,  0.5f,  0.5f),
        vec3(-0.5f,  0.5f,  0.5f),
        vec3(-0.5f, -0.5f,  0.5f),

        vec3( 0.5f, -0.5f, -0.5f),  // -z
        vec3(-0.5f, -0.5f, -0.5f),
        vec3(-0.5f,  0.5f, -0.5f),
        vec3(-0.5f,  0.5f, -0.5f),
        vec3( 0.5f,  0.5f, -0.5f),
        vec3( 0.5f, -0.5f, -0.5f),

        vec3(-0.5f,  0.5f,  0.5f),  // +y
        vec3( 0.5f,  0.5f,  0.5f),
        vec3( 0.5f,  0.5f, -0.5f),
        vec3( 0.5f,  0.5f, -0.5f),
        vec3(-0.5f,  0.5f, -0.5f),
        vec3(-0.5f, -0.5f,  0.5f),

        vec3(-0.5f, -0.5f, -0.5f),  // -y
        vec3( 0.5f, -0.5f, -0.5f),
        vec3( 0.5f, -0.5f,  0.5f),
        vec3( 0.5f, -0.5f,  0.5f),
        vec3(-0.5f, -0.5f, -0.5f),
        vec3(-0.5f, -0.5f,  0.5f),

        vec3( 0.5f, -0.5f,  0.5f),  // +x
        vec3( 0.5f, -0.5f, -0.5f),
        vec3( 0.5f,  0.5f, -0.5f),
        vec3( 0.5f,  0.5f, -0.5f),
        vec3( 0.5f,  0.5f,  0.5f),
        vec3( 0.5f, -0.5f,  0.5f),

        vec3(-0.5f, -0.5f, -0.5f),  // -x
        vec3(-0.5f, -0.5f,  0.5f),
        vec3(-0.5f,  0.5f,  0.5f),
        vec3(-0.5f,  0.5f,  0.5f),
        vec3(-0.5f,  0.5f, -0.5f),
        vec3(-0.5f, -0.5f, -0.5f),
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

void RenderMgr::init() {
    s_window = STD make_shared<Window>();
    s_window->init();
    s_shadowShader = make_shared<Shader>("shaders/shadowmap.vert", "shaders/shadowmap.frag");
    glGenBuffers(1, &s_matricesBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, s_matricesBlock);
    glBufferData(GL_UNIFORM_BUFFER, 144, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glGenBuffers(1, &s_pointLightsBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, s_pointLightsBlock);
    glBufferData(GL_UNIFORM_BUFFER, 484, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glGenBuffers(1, &s_directLightsBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, s_directLightsBlock);
    glBufferData(GL_UNIFORM_BUFFER, 644, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glGenBuffers(1, &s_directLightsBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, s_directLightsBlock);
    glBufferData(GL_UNIFORM_BUFFER, 484, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glGenBuffers(1, &s_lightSpaceMatrixBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, s_lightSpaceMatrixBlock);
    glBufferData(GL_UNIFORM_BUFFER, 64, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glCheckError();
}

void RenderMgr::setCameraMatrices(SharedPtr<Camera> camera)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, s_matricesBlock);
    auto proj = camera->Proj();
    auto view = camera->transform()->View();
    glBindBuffer(GL_UNIFORM_BUFFER, s_matricesBlock);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 64, value_ptr(proj));
    glBufferSubData(GL_UNIFORM_BUFFER, 64, 64, value_ptr(view));
    auto camPos = camera->transform()->position();
    glBufferSubData(GL_UNIFORM_BUFFER, 128, sizeof(vec3), &camPos[0]);
}

//void RenderMgr::setPointLightsBuffer()
//{
//    glBindBufferBase(GL_UNIFORM_BUFFER, 1, s_pointLightsBlock);
//    glBindBuffer(GL_UNIFORM_BUFFER, s_pointLightsBlock);
//    auto scene = SceneMgr::getCurrentScene();
//    auto light = scene->getLights()[0];
//    glBufferSubData(GL_UNIFORM_BUFFER, 0, 12, &light->transform()->position()[0]);
//}

void RenderMgr::setDirectionalLightsBuffer()
{
    glBindBufferBase(GL_UNIFORM_BUFFER, 2, s_directLightsBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, s_directLightsBlock);
    auto scene = SceneMgr::getCurrentScene();
    auto idx = 0;
    auto UnitSize = 64;
    for (auto& light : scene->getLights())
    {
        if (light->lightType() == LightType::Directional)
        {
            auto offsetBase = idx * UnitSize;
            auto color = light->color();
            auto dir = light->transform()->forward();
            auto pos = light->transform()->position();
            auto intensity = light->intensity();
            glBufferSubData(GL_UNIFORM_BUFFER, offsetBase,      sizeof(vec3),  &color[0]);            
            glBufferSubData(GL_UNIFORM_BUFFER, offsetBase + 16, sizeof(vec3),  &dir[0]);
            glBufferSubData(GL_UNIFORM_BUFFER, offsetBase + 32, sizeof(vec3),  &pos[0]);
            glBufferSubData(GL_UNIFORM_BUFFER, offsetBase + 48, sizeof(float), &intensity);
            idx++;
        }
    }
    glBufferSubData(GL_UNIFORM_BUFFER, 480, sizeof(int), &idx);
}

void RenderMgr::setPointLightsBuffer()
{
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, s_pointLightsBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, s_pointLightsBlock);
    auto scene = SceneMgr::getCurrentScene();
    auto idx = 0;
    auto UnitSize = 48;
    for (auto& light : scene->getLights())
    {
        if (light->lightType() == LightType::Point)
        {
            auto offsetBase = idx * UnitSize;
            auto color = light->color();
            auto pos = light->transform()->position();
            auto intensity = light->intensity();
            glBufferSubData(GL_UNIFORM_BUFFER, offsetBase, sizeof(vec3), &color[0]);
            glBufferSubData(GL_UNIFORM_BUFFER, offsetBase + 16, sizeof(vec3), &pos[0]);
            glBufferSubData(GL_UNIFORM_BUFFER, offsetBase + 32, sizeof(float), &intensity);
            idx++;
        }
    }
}

void RenderMgr::setLightSpaceMatrix(mat4 mat)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, 3, s_lightSpaceMatrixBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, s_lightSpaceMatrixBlock);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 64, value_ptr(mat));
}

void RenderMgr::renderShadowMap()
{
    auto scene = SceneMgr::getCurrentScene();
   
    SharedPtr<Light> directionalLight;
    for (auto& l : scene->getLights())
    {
        if (l->lightType() == LightType::Directional)
        {
            directionalLight = l;
            break;
        }
    }
    auto camera = scene->mainCamera;
    auto shader = s_shadowShader;
    shader->use();
    auto view = directionalLight->transform()->View();
    auto proj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 10.0f);
    auto lightSpaceMatrix = proj * view;
    shader->set("lightSpaceMatrix", lightSpaceMatrix);
    auto &buffer = camera->getShadowFrameBuffer();    // 将深度值渲染到此缓冲中
    buffer.bindDepthMapFrameBuffer();
    for (auto& r : scene->getRenderers())
    {
        r->rendering(shader);
        glCheckError();
    }
    setLightSpaceMatrix(lightSpaceMatrix);
}

void RenderMgr::renderPointShadow()
{
    auto scene = SceneMgr::getCurrentScene();
    auto camera = scene->mainCamera;
    auto& buffer = camera->getPointShadowFrameBuffer();
    buffer.bindCubeMapDepthMapFrameBuffer();
    SharedPtr<Light> pointLight;
    for (auto& l : scene->getLights())
    {
        if (l->lightType() == LightType::Point)
        {
            pointLight = l;
            break;
        }
    }
    auto shader = make_shared<Shader>("shaders/pointshadowmap.vert", "shaders/pointshadowmap.frag", "shaders/pointshadowmap.geom");
    shader->use();
    shader->set("lightPos", pointLight->transform()->position());
    shader->set("far_plane", 25.0f);
    glm::mat4 shadowProj = glm::perspective(radians(90.0f), 1.0f, 0.1f, 25.0f);
    //glm::mat4 shadowProj = glm::perspective(90.0f, 1.0f, 0.1f, 25.0f);  // 这是错误的
    auto lightPos = pointLight->transform()->position();
    std::vector<glm::mat4> shadowTransforms;
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));
    
    for (int i = 0; i < shadowTransforms.size(); i++)
    {
        shader->set(("shadowMatrices[" + to_string(i) + "]").c_str(), shadowTransforms[i]);
    }
    
    for (auto& e : scene->getRenderers())
    {
        if (e->gameObject()->getComponent<Light>() || !e->castShadow)
            continue;
        e->rendering(shader);
        glCheckError();
    }
}

void RenderMgr::rendering() {
    auto res = s_window->prepare();

    auto scene = SceneMgr::getCurrentScene();
    // 生成阴影贴图
    //renderShadowMap();
    //renderPointShadow();
    // 获取光照信息
    // 获取相机参数
    auto mainCamera = scene->mainCamera;
    setCameraMatrices(mainCamera);
    //setDirectionalLightsBuffer();
    //setPointLightsBuffer();
    // 获取所有Renderer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 800, 600);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    //glClear(GL_STENCIL_BUFFER_BIT);
    auto shadowTex = make_shared<Texture>(mainCamera->getShadowFrameBuffer().dep);
    auto pointShadowTex = make_shared<Texture>(mainCamera->getPointShadowFrameBuffer().dep, TextureType::TextureCube);
    for (auto e : getRenderers())
    {
        //e->material->setTexture("_ShadowMap", shadowTex);
        //e->material->setTexture("_PointShadowMap", pointShadowTex);
        e->rendering();
        glCheckError();
    }
    renderSkyBox();
    s_window->finish();
    if (!res)
    {
        s_window->terminate();
        Application::instance().exit();
    }
}

SharedPtrVector<Renderer> RenderMgr::getRenderers()
{
    auto scene = SceneMgr::getCurrentScene();
    auto renderers = scene->getRenderers();
    //sort(renderers.begin(), renderers.end(), [](SharedPtr<Renderer> r) {return r->renderQueue; });
    return renderers;
}

void RenderMgr::renderSkyBox()
{
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    auto scene = SceneMgr::getCurrentScene();
    auto skybox = scene->skyBox;
    if (!skybox)
        return;
    auto mat = skybox->material;
    auto shader = mat->shader;
    shader->use();
    glActiveTexture(GL_TEXTURE0);
    auto tid = mat->getTexture("_SkyBoxA")->getTextureID();
    glBindTexture(GL_TEXTURE_CUBE_MAP, tid);
    //shader->use();
    //mat->setShaderTexture(shader);
    auto filter = skybox->gameObject()->getComponent<MeshFilter>();
    auto mesh = filter->sharedMesh;
    mesh->draw();
    glCheckError();
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
}