#pragma once

#include "Object.h"
#include "SceneMgr.h"
#include "Window.h"
#include "Application.h"
#include "Renderer.h"
#include "Camera.h"

namespace yk
{
	class RenderMgr : public Object
	{
	public:
		static void init() {
			s_window = STD make_shared<Window>();
			s_window->init();
			glGenBuffers(1, &s_matricesBlock);
			glBindBuffer(GL_UNIFORM_BUFFER, s_matricesBlock);
			glBufferData(GL_UNIFORM_BUFFER, 144, NULL, GL_STATIC_DRAW);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);

			glGenBuffers(1, &s_pointLightsBlock);
			glBindBuffer(GL_UNIFORM_BUFFER, s_pointLightsBlock);
			glBufferData(GL_UNIFORM_BUFFER, 16, NULL, GL_STATIC_DRAW);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		static void rendering() {
			auto res = s_window->prepare();
			
			auto scene = SceneMgr::getCurrentScene();
			// 获取光照信息
			// 获取相机参数
			auto mainCamera = scene->mainCamera;
			setCameraMatrices(mainCamera);
			setPointLightsBuffer();
			// 获取所有Renderer
			for (auto e : scene->getRenderers())
			{
				e->rendering();
			}
			s_window->finish();
			if (!res)
			{
				s_window->terminate();
				Application::instance().exit();
			}
		}
		static SharedPtr<Window> window() { return s_window; }
	private:
		static SharedPtr<Window> s_window;
		static unsigned int s_matricesBlock;
		static unsigned int s_pointLightsBlock;
		static void setCameraMatrices(SharedPtr<Camera> camera);
		static void setPointLightsBuffer();

	};
}