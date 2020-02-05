#pragma once

#include "Object.h"
namespace yk
{
	class Transform;
	class GameObject;
	class Component : public Object
	{
		META_OBJECT
	public:
		STD shared_ptr<GameObject> gameObject() { return m_gameObject.lock(); }
		STD shared_ptr<Transform> transform();

	private:
		friend class GameObject;
		STD weak_ptr<GameObject> m_gameObject;
	};
}