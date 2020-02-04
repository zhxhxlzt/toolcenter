#pragma once

#include "Object.h"

namespace yk
{
	class GameObject;
	class Transform;
	class BaseComponent : public Object
	{
		META_OBJECT
	public:
		BaseComponent() : Object() {}
		STD shared_ptr<GameObject> gameObject() { return m_gameObject.lock(); }
		STD shared_ptr<Transform> transform() { return m_transform.lock(); }

	private:
		friend class GameObject;
		STD weak_ptr<GameObject> m_gameObject;
		STD weak_ptr<Transform> m_transform;
	};
}