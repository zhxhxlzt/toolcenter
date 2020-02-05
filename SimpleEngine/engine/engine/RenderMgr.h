#pragma once

#include "Object.h"
#include "SceneMgr.h"
#include "Window.h"
#include "Application.h"
#include "Renderer.h"

namespace yk
{
	class RenderMgr : public Object
	{
	public:
		static void init() {
			s_window = STD make_shared<Window>();
			s_window->init();
		}

		static void rendering() {
			auto res = s_window->prepare();
			
			auto scene = SceneMgr::getCurrentScene();
			// 获取光照信息
			// 获取相机参数
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
	};
}