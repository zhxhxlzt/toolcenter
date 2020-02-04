#include "Object.h"

using namespace yk;
using namespace std;


Object::Object()
{
	static int objectId = 0;
	m_instanceID = objectId++;
}

int Object::getInstanceID()
{
	return m_instanceID;
}

string Object::toString()
{
	return className() + "_" + to_string(m_instanceID);
}

void Object::setParent(STD shared_ptr<Object> parent)
{
	if (parent)
	{
		auto& children = parent->m_children;
		auto self = shared_from_this();
		auto res = find(children.begin(), children.end(), self);
		if (res == children.end())
			children.push_back(move(self));
	}
	else if (!m_parent.expired())
	{
		// 从自身的parent中移除自己
		parent = m_parent.lock();
		auto& children = parent->m_children;
		auto self = shared_from_this();
		remove(children.begin(), children.end(), self);
	}
}

vector<shared_ptr<Object>> Object::children()
{
	return m_children;
}

shared_ptr<Object> Object::findChild(string& name)
{
	auto it = find_if(m_children.begin(), m_children.end(),
		[&](auto& child) { return child->name == name; });
	if (it != m_children.end())
		return *it;
	return nullptr;
}

shared_ptr<Object> Object::findChild(string&& name)
{
	return findChild(name);
}

Object::operator bool() const
{
	return m_alive;
}