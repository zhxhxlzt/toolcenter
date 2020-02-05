#include<iostream>
#include<ykEngine.h>
#include "testScene.h"
using namespace std;
using namespace yk;

int main()
{
	Application app;
	GameMgr::start();
	
	auto scene = getTestScene();
	SceneMgr::setCurrentScene(scene);
	app.exec();
	return 0;
}
