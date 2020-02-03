#include "TimerMgr.h"
using namespace yk;

TimerMgr* TimerMgr::s_instance = nullptr;

TimerMgr& TimerMgr::instance()
{
	if (!s_instance)
		s_instance = new TimerMgr();
	return *s_instance;
}

void TimerMgr::schedule()
{
	auto it = m_activeTimers.begin();
	while (it != m_activeTimers.end())
	{
		auto timer = *it;
		if (timer->getExpireTime() <= system_clock::now())
		{
			m_activeTimers.erase(timer);
			timer->call();
			it = m_activeTimers.begin();	// 设置it为最近时间的timer
		}
		else
		{	// 后续timer的expire时间都大于当前时间
			break;
		}
	}
}

time_point<system_clock> TimerMgr::nextTimerCallTimePoint()
{
	auto it = m_activeTimers.begin();
	if (it != m_activeTimers.end())
		return (*it)->getExpireTime();
	return system_clock::now();
}

void TimerMgr::addTimer(STD shared_ptr<Timer> timer)
{
	if (m_activeTimers.find(timer) == m_activeTimers.end())
		m_activeTimers.insert(timer);
}

void TimerMgr::delTimer(STD shared_ptr<Timer> timer)
{
	m_activeTimers.erase(timer);
}