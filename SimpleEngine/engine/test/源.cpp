//#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#include<iostream>
#include<ykEngine.h>
#include "testScene.h"
using namespace std;
using namespace yk;
#include<string>
#include<iostream>
#include<algorithm>
#include<stack>
#include<array>
#include<queue>
#include<xtree>
#include<map>
#include<set>
#include<list>
#include<unordered_set>

#include<set>

#include<atomic>
#include<iomanip>
#include<fstream>

namespace ok
{
	using namespace std;

	void testFp()
	{
		ofstream f;
		f.open("hello.txt", ios::trunc);
		f.tie(&cout);

		cout << "hello world!" << endl;
		f.close();
	}
}


int main1()
{
	ok::testFp();
	getchar();
	return 0;
}
int main()
{
	Application app;
	GameMgr::start();
	auto scene = getTestScene();
	SceneMgr::setCurrentScene(scene);
	app.exec();
	return 0;
}
