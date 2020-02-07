#include "RenderMgr.h"
#include "Camera.h"
#include "Transform.h"
#include "Light.h"
using namespace yk;

SharedPtr<Window> RenderMgr::s_window = nullptr;
unsigned int RenderMgr::s_matricesBlock = -1;
unsigned int RenderMgr::s_pointLightsBlock = -1;

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

void RenderMgr::setPointLightsBuffer()
{
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, s_pointLightsBlock);
    glBindBuffer(GL_UNIFORM_BUFFER, s_pointLightsBlock);
    auto scene = SceneMgr::getCurrentScene();
    auto light = scene->getLights()[0];
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 12, &light->transform()->position()[0]);
}