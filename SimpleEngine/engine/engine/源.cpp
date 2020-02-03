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

void testset()
{
	set<int> s = { 3, 9, 4, 2, 8 };
	for (auto e : s)
	{
		cout << e << endl;
	}
}


int main()
{
	Delegate<> D1;
	D1 += f1;
	D1 += f2;
	D1 += f3;
	D1();
	cout << "======Ê¹ÓÃD2()" << endl;
	Delegate<> D2;
	D2 += D1;
	D2();
	D2 -= D1;
	cout << "======D2 -= D1ºó" << endl;
	D2();
	getchar();
	return 0;
}