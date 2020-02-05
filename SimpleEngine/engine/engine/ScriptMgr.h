#pragma once

#include "Object.h"
#include "SceneMgr.h"
#include "MonoBehaviour.h"
namespace yk
{
	class ScriptMgr
	{
	public:
		static void addNewMonoBehaviours(SharedPtr<MonoBehaviour> mb) { m_newMonoBehaviours.push_back(mb); }
		static void update()
		{
			for (auto& mb : m_newMonoBehaviours)
				mb->Start();
			m_newMonoBehaviours.clear();

			auto scene = SceneMgr::getCurrentScene();
			for (auto& mb : scene->getMonoBehaviours())
			{
				mb->Update();
			}
		}
		static void LateUpdate()
		{
			for (auto& mb : m_newMonoBehaviours)
				mb->Start();
			m_newMonoBehaviours.clear();

			auto scene = SceneMgr::getCurrentScene();
			for (auto& mb : scene->getMonoBehaviours())
			{
				mb->LateUpdate();
			}
		}

	private:
		static SharedPtrVector<MonoBehaviour> m_newMonoBehaviours;
	};
}