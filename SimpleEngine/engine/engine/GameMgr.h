#pragma once

#include "Object.h"
#include "TimerMgr.h"
#include "RenderMgr.h"
#include "Window.h"
namespace yk
{
	class GameMgr
	{
	public:
		static void start() {
			RenderMgr::init();
			m_gameUpdate = STD make_shared<Timer>();
			m_gameUpdate->timeOut += update;
			m_gameUpdate->start(1000 / 60);
		}
		static void update() {
			// 渲染更新
			// 事件更新
			RenderMgr::rendering();
		}
		static void exit() {
			m_gameUpdate->timeOut -= update;
			glfwTerminate();
		}

	private:
		static SharedPtr<Timer> m_gameUpdate;
	};
}