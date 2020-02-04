#pragma once
#include "Object.h"
//#include "GameObject.h"
#include "Renderer.h"
#include "Light.h"

namespace yk
{
	using GameObjectList = Vector<SharedPtr<GameObject>>;
	using RendererList = Vector<SharedPtr<Renderer>>;
	class GameObject;
	class Scene
	{
	public:
		GameObjectList getRootGameObjects() { return m_rootGameObjects; }
		void addRootGameObject(SharedPtr<GameObject> gameObject) { m_rootGameObjects.push_back(gameObject); }
		void delRootGameObject(SharedPtr<GameObject> gameObject) {
			STD remove(m_rootGameObjects.begin(), m_rootGameObjects.end(), gameObject);
		}

		RendererList getRenderers();

	private:
		GameObjectList m_rootGameObjects;
	};
}