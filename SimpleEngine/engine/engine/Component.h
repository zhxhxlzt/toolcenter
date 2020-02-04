#pragma once

#include "BaseComponent.h"
namespace yk
{
	class Component : public BaseComponent
	{
		META_OBJECT
	public:
		Component() : BaseComponent() {}
		/*template<class T>
		STD shared_ptr<T> addComponent()
		{
			return gameObject()->addComponent<T>();
		}

		template<class T>
		STD shared_ptr<T> getComponent()
		{
			return gameObject()->getComponent<T>();
		}*/
	};
}