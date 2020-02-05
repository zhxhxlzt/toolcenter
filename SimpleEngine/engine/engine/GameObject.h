#pragma once
#include "Object.h"
#include "Component.h"
#include "SceneMgr.h"
#include <assert.h>
#include <Renderer.h>
#include <queue>
#include "Camera.h"
namespace yk
{
	class Transform;
	class GameObject : public Object
	{
		META_OBJECT
	public:
		static SharedPtr<GameObject> create();
		template<class T>
		STD shared_ptr<T> addComponent()
		{
			return _addComponent<T>(STD is_base_of<Component, T>());
		}

		template<class T>
		STD shared_ptr<T> getComponent()
		{
			auto meta = T::metaObject();
			for (auto& comp_ptr : m_components)
			{
				auto comp_meta = comp_ptr->getMetaObject();
				if (comp_meta == meta || comp_meta->inherits(meta))
					return STD static_pointer_cast<T>(comp_ptr);
			}
			return nullptr;
		}

		template<class T>
		STD vector<STD shared_ptr<T>> getComponents()
		{
			STD vector<STD shared_ptr<T>> comps;
			auto meta = T::metaObject();
			for (auto& comp_ptr : m_components)
			{
				auto comp_meta = comp_ptr->getMetaObject();
				if (comp_meta == meta || comp_meta->inherits(meta))
					comps.push_back(STD static_pointer_cast<T>(comp_ptr));
			}
			return comps;
		}

		template<class T>
		STD vector<STD shared_ptr<T>> getComponentsInChildren()
		{
			STD vector<STD shared_ptr<T>> comps;
			for (auto obj : children())
			{
				if (obj->getMetaObject() == GameObject::metaObject())
				{
					auto gb = STD static_pointer_cast<GameObject>(obj);
					auto gb_comps = gb->getComponents<T>();
					comps.insert(comps.end(), gb_comps.begin(), gb_comps.end());
					auto gb_child_comps = gb->getComponentsInChildren<T>();
					comps.insert(comps.end(), gb_child_comps.begin(), gb_child_comps.end());
				}
			}
			return comps;
		}

		STD shared_ptr<Transform> transform();
		void delComponent(SharedPtr<Component> comp) {
			auto it = STD find(m_components.begin(), m_components.end(), comp);
			if (it != m_components.end())
			{
				m_components.erase(it);
				checkDelComponent(comp);
			}
		}
		bool active = true;
	private:
		template<class T>
		STD shared_ptr<T> _addComponent(STD true_type)
		{
			auto comp_ptr = STD make_shared<T>();
			comp_ptr->m_gameObject = STD static_pointer_cast<GameObject>(shared_from_this());
			m_components.push_back(comp_ptr);
			checkAddComponent(comp_ptr);
			return comp_ptr;
		}
		template<class T>
		STD shared_ptr<T> _addComponent(STD false_type) { 
			STD cout << "不能将类型<" << T::metaObject()->className << ">作为GameObject的组件!" << STD endl;
			return nullptr; 
		}
		void checkAddComponent(STD shared_ptr<Component> comp);
		void checkDelComponent(STD shared_ptr<Component> comp);
		STD vector<STD shared_ptr<Component>> m_components;
	};
}