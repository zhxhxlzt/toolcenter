#pragma once

#include "Object.h"
#include <iterator>

template<typename... ArgsType>
class Delegate : public Object
{
public:
	Delegate(Delegate<ArgsType...>& ) = delete;
	Delegate(Delegate<ArgsType...> &&) = delete;
	Delegate() = default;
	using FnType = void(*)(ArgsType...);
	void operator +=(STD function<void(ArgsType...)> observer)
	{
		m_observers.push_back(observer);
	}
	void operator +=(Delegate<ArgsType...>& delegate)
	{
		m_delegates.push_back(&delegate);
	}

	void operator -=(STD function<void(ArgsType...)> observer)
	{
		size_t tarAddr = getFunctionAddr(observer);
		auto it = STD remove_if(m_observers.begin(), m_observers.end(),
			[=](auto& ob)
		{
			auto addr = *(size_t*)ob.target<FnType>();
			return addr == tarAddr;
		});
		m_observers.erase(it, m_observers.end());
	}

	void operator -=(Delegate<ArgsType...>& delegate)
	{
		auto dele_ptr = &delegate;
		auto it = STD remove_if(m_delegates.begin(), m_delegates.end(), [=](Delegate* dele)
		{
			return dele == dele_ptr;
		});
		m_delegates.erase(it, m_delegates.end());
	}

	void operator()(ArgsType... args)
	{
		STD for_each(
			m_observers.begin(), m_observers.end(),
			[=](auto& ob) { ob(args...); });

		STD for_each(
			m_delegates.begin(), m_delegates.end(), [=](Delegate* dele)
		{
			(*dele)(args...);
		});
	}

private:
	size_t getFunctionAddr(STD function<void(ArgsType...)> &func)
	{
		return *(size_t*)func.target<FnType>();
	}
	STD vector<STD function<void(ArgsType...)>> m_observers;
	STD vector<Delegate*> m_delegates;
};