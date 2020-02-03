#pragma once
#include<iostream>
#include "Object.h"

#include "GameObject.h"
#include "BaseComponent.h"
#include "Transform.h"
#include "Component.h"
#include "Delegate.h"
#include <iterator>
#include <Windows.h>
#include <typeinfo>
#include <typeinfo.h>
#include "Application.h"
#include "Timer.h"
using namespace std;

void showClassInfo(Object* o)
{
	auto m = o->getMetaObject();
	cout << "class name:		" << m->className << endl;
	cout << "class id:			" << m->classID << endl;
	cout << "base class name:	" << m->baseClassName << endl;
	cout << "base class id:		" << m->baseClassID << endl;
}
void run()
{
	static int i = 0;
	cout << "runing" << i++ << endl;
}
static auto point = system_clock::now();
void showTime(string s)
{
	auto d = system_clock::now() - point;
	cout << s << "time:" << duration_cast<chrono::milliseconds>(d).count() << endl;
}
int main()
{
	Application app;
	//vector<shared_ptr<Timer>> timers;
	for (int i = 0; i < 100; i++)
	{
		auto t = make_shared<Timer>();
		t->timeOut += run;
		t->start(i * 100, true);
	}

	app.exec();
	getchar();
	return 0;
}