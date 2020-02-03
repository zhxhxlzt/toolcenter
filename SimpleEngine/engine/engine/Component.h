#pragma once

#include "BaseComponent.h"
#include "GameObject.h"
namespace yk
{
	class Component : public BaseComponent
	{
		META_OBJECT
	public:
		template<class T>
		STD shared_ptr<T> addComponent()
		{
			return gameObject()->addComponent<T>();
		}

		template<class T>
		STD shared_ptr<T> getComponent()
		{
			return gameObject()->getComponent<T>();
		}
	};
}