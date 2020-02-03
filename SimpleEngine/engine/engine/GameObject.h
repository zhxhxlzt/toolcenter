#pragma once
#include "Object.h"
#include "BaseComponent.h"

class GameObject : public Object, public STD enable_shared_from_this<GameObject>
{
	META_OBJECT
public:
	template<class T>
	STD shared_ptr<T> addComponent()
	{
		auto comp_ptr = STD make_shared<T>();
		comp_ptr->m_gameObject = shared_from_this();
		m_components.push_back(comp_ptr);
		return comp_ptr;
	}

	template<class T>
	STD shared_ptr<T> getComponent()
	{
		auto meta = T::getMetaObject();
		for (auto &comp_ptr : m_components)
		{
			auto comp_meta = comp_ptr->getMetaObject();
			if (comp_meta.inherits(meta))
				return comp_ptr;
		}
		return nullptr;
	}


private:
	STD vector<STD shared_ptr<BaseComponent>> m_components;
};

