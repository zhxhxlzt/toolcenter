#pragma once
#include <string>
#define STD std::

struct MetaObject
{
	STD string className;
	STD string baseClassName;
};

#define Q_OBJECT		\
public:		\
	static MetaObject _metaObject;	\
	STD string className(){ return _metaObject.className;}	\
	STD string baseClassName() {return _metaObject.baseClassName; }

class Object
{
	Q_OBJECT
public:
	void func1();
	void func2();
};
