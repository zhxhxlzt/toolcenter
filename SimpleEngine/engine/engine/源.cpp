#pragma once
#include<iostream>
#include "Object.h"
#include "World.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "Transform.h"
#include "Component.h"
#include "Delegate.h"
#include <iterator>
#include <Windows.h>
#include <typeinfo>
#include <typeinfo.h>
using namespace std;

void showClassInfo(Object* o)
{
	auto m = o->getMetaObject();
	cout << "class name:		" << m->className << endl;
	cout << "class id:			" << m->classID << endl;
	cout << "base class name:	" << m->baseClassName << endl;
	cout << "base class id:		" << m->baseClassID << endl;
}


void f1()
{
	cout << "f1" << endl;
}
void f2()
{
	cout << "f2" << endl;
}
void f3()
{
	cout << "f3" << endl;
}

int main()
{
	auto gb = make_shared<GameObject>();
	gb->addComponent<Transform>();
	auto tr = gb->getComponent<BaseComponent>();
	getchar();
	return 0;
}