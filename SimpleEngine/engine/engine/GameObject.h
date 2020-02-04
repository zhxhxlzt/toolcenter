#pragma once
#include "Object.h"
#include "BaseComponent.h"
#include <assert.h>
namespace yk
{
	class GameObject : public Object
	{
		META_OBJECT
	public:
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

	private:
		template<class T>
		STD shared_ptr<T> _addComponent(STD true_type)
		{
			auto meta = T::metaObject();
			assert(meta->inherits(BaseComponent::metaObject()));
			auto comp_ptr = STD make_shared<T>();
			comp_ptr->m_gameObject = STD static_pointer_cast<GameObject>(shared_from_this());
			m_components.push_back(comp_ptr);
			return comp_ptr;
		}
		template<class T>
		STD shared_ptr<T> _addComponent(STD false_type) { 
			STD cout << "���ܽ�����<" << T::metaObject()->className << ">��ΪGameObject�����!" << STD endl;
			return nullptr; 
		}
		STD vector<STD shared_ptr<BaseComponent>> m_components;
	};
}