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
void run(int a)
{
	cout << "run" << a << endl;
}

void say(string name)
{
	cout << "my name is: " << name << endl;
}
class A
{
public:
	A() { cout << "construct A" << endl; }
	A(const A& a) { cout << "copy A" << endl; }
	A(const A&& a) { cout << "move A" << endl; }
};
int main()
{
	auto gb = make_shared<GameObject>();
	auto ms = gb->addComponent<Behaviour>();
	auto tr = ms->transform();
	getchar();
	return 0;
}

//	Application app;
//	auto t = make_shared<Timer>();
//	t->timeOut += run;
//	t->start(1000);
//	auto window = make_shared<yk::Window>();
//	window->init();
//
//	auto t2 = make_shared<Timer>();
//	t->timeOut += run;
//
//	while (true)
//	{
//		window->prepare();
//		window->finish();
//	}
//	
//	app.exec();
//	getchar();
//	return 0;
//}