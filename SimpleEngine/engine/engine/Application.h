#pragma once
#include "Object.h"
#include <assert.h>
#include "TimerMgr.h"

namespace yk
{
	class Application : public Object
	{
		META_OBJECT

	public:
		Application& instance();
		Application();
		void exec();
		void exit();

	private:
		bool m_shutdown = false;
		static Application* s_instance;
	};
}