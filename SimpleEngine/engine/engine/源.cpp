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
	//cout << "runing" << i++ << endl;
	auto t = make_shared<Timer>();
	t->timeOut += [&]() { cout << "hello" << i++ << endl; };
	t->start(i * 500, true);
}

struct A : enable_shared_from_this<A>
{
public:
	shared_ptr<A> get()
	{
		return shared_from_this();
	}
};

class B : public enable_shared_from_this<B>
{
public:
	shared_ptr<B> get()
	{
		return shared_from_this();
	}
};


int main()
{
	Application app;
	auto t = make_shared<Timer>();
	t->timeOut += run;
	t->start(100);
	auto t1 = make_shared<Timer>();
	t1->timeOut += [&]() { t->stop(); };
	t1->start(1000);
	app.exec();
	getchar();
	return 0;
}