#include "Timer.h"
#include "TimerMgr.h"
using namespace yk;

static size_t timerID = 0;

void Timer::start(size_t interval, bool singleShoot)
{
	auto p = shared_from_this();
	TimerMgr::instance().delTimer(shared_from_this());
	m_singleShoot = singleShoot;
	m_interval = milliseconds(interval);
	m_timerID = timerID++;
	resetExpireTime();
	TimerMgr::instance().addTimer(shared_from_this());
}

void Timer::stop()
{
	TimerMgr::instance().delTimer(shared_from_this());
}

void Timer::call()
{
	timeOut();
	if (!m_singleShoot)
	{
		resetExpireTime();
		TimerMgr::instance().addTimer(shared_from_this());
	}
}

void Timer::setSingleShoot(bool s)
{
	m_singleShoot = s;
}

time_point<system_clock>& Timer::getExpireTime()
{
	return m_expirePoint;
}

bool Timer::operator<(const Timer& right) const
{
	return m_expirePoint < right.m_expirePoint;
}

void Timer::resetExpireTime()
{
	m_startPoint = system_clock::now();
	m_expirePoint = m_startPoint + m_interval;
}