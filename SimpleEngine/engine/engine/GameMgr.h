#pragma once

#include "Object.h"
#include "TimerMgr.h"
#include "RenderMgr.h"
#include "ScriptMgr.h"
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
			ScriptMgr::update();
			// äÖÈ¾¸üÐÂ
			RenderMgr::rendering();
			ScriptMgr::LateUpdate();
		}
		static void exit() {
			m_gameUpdate->timeOut -= update;
			glfwTerminate();
		}

	private:
		static SharedPtr<Timer> m_gameUpdate;
	};
}