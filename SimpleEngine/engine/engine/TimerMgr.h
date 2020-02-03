#pragma once

#include "Object.h"
#include "Timer.h"
#include <chrono>
namespace yk
{
	using namespace std::chrono;
	class TimerMgr : public Object
	{
		META_OBJECT
	public:
		static TimerMgr& instance();
		void schedule();
		time_point<system_clock> nextTimerCallTimePoint();
		void addTimer(STD shared_ptr<Timer> timer);
		void delTimer(STD shared_ptr<Timer> timer);

	private:
		STD set<STD shared_ptr<Timer>> m_activeTimers;
		static TimerMgr* s_instance;
	};
}