#pragma once
#include "Object.h"

namespace yk
{
	class GameObject;
	class Light;
	class Camera;
	class Renderer;
	class MonoBehaviour;
	class SkyBox;
	class Scene
	{
	public:
		SharedPtrVector<GameObject> getRootGameObjects() { return m_rootGameObjects; }
		void addRootGameObject(SharedPtr<GameObject> gameObject) { m_rootGameObjects.push_back(gameObject); }
		void delRootGameObject(SharedPtr<GameObject> gameObject) {
			STD remove(m_rootGameObjects.begin(), m_rootGameObjects.end(), gameObject);
		}
		void AddRenderer(SharedPtr<Renderer> renderer) { m_renderers.push_back(renderer); }
		void DelRenderer(SharedPtr<Renderer> renderer) { STD remove(m_renderers.begin(), m_renderers.end(), renderer); }
		void AddMonoBehaviour(SharedPtr<MonoBehaviour> mb) { m_monoBehaviours.push_back(mb); }
		void DelMonoBehaviour(SharedPtr<MonoBehaviour> mb) { STD remove(m_monoBehaviours.begin(), m_monoBehaviours.end(), mb); }
		void AddLight(SharedPtr<Light> lt) { m_lights.push_back(lt); }
		void DelLight(SharedPtr<Light> lt) { STD remove(m_lights.begin(), m_lights.end(), lt); }
		SharedPtrVector<Renderer> getRenderers() { return m_renderers; }
		SharedPtrVector<MonoBehaviour> getMonoBehaviours() { return m_monoBehaviours; }
		SharedPtrVector<Light> getLights() { return m_lights; }
		SharedPtr<Camera> mainCamera;
		SharedPtr<SkyBox> skyBox;

	private:
		SharedPtrVector<GameObject> m_rootGameObjects;
		SharedPtrVector<Renderer>	m_renderers;
		SharedPtrVector<MonoBehaviour> m_monoBehaviours;
		SharedPtrVector<Light> m_lights;
	};
}