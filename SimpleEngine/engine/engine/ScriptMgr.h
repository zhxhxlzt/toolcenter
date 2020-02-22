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
			auto scene = SceneMgr::getCurrentScene();
			for (auto& mb : m_newMonoBehaviours)
			{
				mb->Start();
				scene->AddMonoBehaviour(mb);
			}
			m_newMonoBehaviours.clear();
			for (auto& mb : scene->getMonoBehaviours())
			{
				mb->Update();
			}
		}
		static void LateUpdate()
		{
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