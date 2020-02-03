#include "Application.h"
#include <Windows.h>
#include <iostream>
using namespace yk;
Application* Application::s_instance = nullptr;

Application& Application::instance()
{
	return *s_instance;
}

Application::Application()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

void Application::exec()
{
	while (!m_shutdown)
	{
		auto targetTimePoint = TimerMgr::instance().nextTimerCallTimePoint();
		if (system_clock::now() < targetTimePoint)
		{
			auto ms = duration_cast<milliseconds>(targetTimePoint - system_clock::now()).count();
			Sleep(ms);
		}	
		TimerMgr::instance().schedule();
	}
}

void Application::exit()
{
	m_shutdown = true;
}