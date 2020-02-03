#pragma once
#include "Object.h"
#include "Delegate.h"
#include <chrono>
using namespace std::chrono;
class Timer : public Object
{
	META_OBJECT
public:
	Delegate<> timeOut;
	/*Timer(function<void(void)> target, unsigned int ms) :
		m_target(target),
		m_milliseconds(milliseconds(ms))
	{
	}*/
	
private:
	time_point<system_clock> m_startPoint;
	milliseconds m_milliseconds;
	//function<void(void)> m_target;
};