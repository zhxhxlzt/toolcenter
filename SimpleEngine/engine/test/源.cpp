#include<iostream>
#include <Application.h>
#include <set>
#include <Window.h>
#include <string>
#include <vector>
#include <GameObject.h>
#include <Mesh.h>
#include <Transform.h>
#include <Behaviour.h>
using namespace std;
using namespace yk;

#include <Delegate.h>
#include <Timer.h>
#include <GameMgr.h>
#include <Shader.h>
#include <stdlib.h>

#include "testScene.h"
#include <MeshRenderer.h>
int main()
{
	Application app;
	GameMgr::start();
	auto scene = getTestScene();
	SceneMgr::setCurrentScene(scene);
	app.exec();
	return 0;
}
