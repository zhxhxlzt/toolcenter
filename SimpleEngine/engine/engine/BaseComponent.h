#pragma once

#include "Object.h"
class GameObject;
class BaseComponent : public Object
{
	META_OBJECT
public:
	
	STD shared_ptr<GameObject> gameObject() { return m_gameObject.lock(); }

private:
	friend class GameObject;
	STD weak_ptr<GameObject> m_gameObject;
};