//#pragma once
//#include<iostream>
//#include "Object.h"
//
//#include "GameObject.h"
//#include "BaseComponent.h"
//#include "Transform.h"
//#include "Component.h"
//#include "Delegate.h"
//#include <iterator>
//#include <Windows.h>
//#include "Application.h"
//#include "Timer.h"
//using namespace std;
//
//void showClassInfo(Object* o)
//{
//	auto m = o->getMetaObject();
//	cout << "class name:		" << m->className << endl;
//	cout << "class id:			" << m->classID << endl;
//	cout << "base class name:	" << m->baseClassName << endl;
//	cout << "base class id:		" << m->baseClassID << endl;
//}
//
//void run()
//{
//	cout << "runing" << endl;
//}
//
//int main()
//{
//	Application app;
//	auto t = make_shared<Timer>();
//	t->timeOut += run;
//	t->start(1000);
//	app.exec();
//	return 0;
//}
