#pragma once
#include "Object.h"
#include "Delegate.h"
#include <chrono>
using namespace std::chrono;
class Timer : public Object, public STD enable_shared_from_this<Timer>
{
	META_OBJECT
public:
	Delegate<> timeOut;
	void start(size_t interval, bool singleShoot=false);
	void stop();
	void call();
	void setSingleShoot(bool singleShoot);
	time_point<system_clock>& getExpireTime();
	bool operator<(const Timer& right) const;

private:
	void resetExpireTime();
	time_point<system_clock> m_startPoint;
	time_point<system_clock> m_expirePoint;
	milliseconds m_interval;
	bool m_singleShoot = false;
	bool m_active = true;
	bool m_stoped = false;
	size_t m_timerID = -1;
};