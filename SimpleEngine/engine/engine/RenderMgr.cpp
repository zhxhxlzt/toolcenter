#include "RenderMgr.h"
#include "Camera.h"
#include "Transform.h"

using namespace yk;

SharedPtr<Window> RenderMgr::s_window = nullptr;
unsigned int RenderMgr::s_matricesBlock = -1;

void RenderMgr::setCameraMatrices(SharedPtr<Camera> camera)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, s_matricesBlock);
    auto proj = camera->Proj();
    auto view = camera->transform()->View();
    glBindBuffer(GL_UNIFORM_BUFFER, s_matricesBlock);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, 64, value_ptr(proj));
    glBufferSubData(GL_UNIFORM_BUFFER, 64, 64, value_ptr(view));
}