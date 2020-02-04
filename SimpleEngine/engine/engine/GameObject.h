#pragma once
#include "Object.h"
#include "BaseComponent.h"
#include "SceneMgr.h"
#include <assert.h>
#include <Renderer.h>
#include <queue>
namespace yk
{
	class Transform;
	class GameObject : public Object
	{
		META_OBJECT
	public:
		GameObject();
		~GameObject();
		static SharedPtr<GameObject> create();
		template<class T>
		STD shared_ptr<T> addComponent()
		{
			return _addComponent<T>(STD is_base_of<BaseComponent, T>());
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
					//comps.insert(comps.end(), childComps.begin(), childComps.end());
				}
			}
			return comps;
		}

		STD shared_ptr<Transform> transform();
		bool active = true;
	private:
		template<class T>
		STD shared_ptr<T> _addComponent(STD true_type)
		{
			auto comp_ptr = STD make_shared<T>();
			comp_ptr->m_gameObject = STD static_pointer_cast<GameObject>(shared_from_this());
			comp_ptr->m_transform = m_transform;
			m_components.push_back(comp_ptr);
			return comp_ptr;
		}
		template<class T>
		STD shared_ptr<T> _addComponent(STD false_type) { 
			STD cout << "不能将类型<" << T::metaObject()->className << ">作为GameObject的组件!" << STD endl;
			return nullptr; 
		}
		STD vector<STD shared_ptr<BaseComponent>> m_components;
		STD shared_ptr<Transform> m_transform;
	};
}