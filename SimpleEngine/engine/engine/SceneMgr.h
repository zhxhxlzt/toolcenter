#pragma once

#include "Scene.h"

namespace yk
{
	class SceneMgr
	{
	public:
		static void setCurrentScene(STD shared_ptr<Scene> scene) { s_currentScene = scene; }
		static SharedPtr<Scene> getCurrentScene() { return s_currentScene; }

	private:
		static STD shared_ptr<Scene> s_currentScene;
	};
}