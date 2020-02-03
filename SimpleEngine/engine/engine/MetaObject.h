#pragma once
#include <map>
#include <string>
#define STD std::


struct MetaObject
{
	const STD string className;
	const STD string baseClassName;
	const int classID;
	const int baseClassID;
	const MetaObject* baseMetaObject();
	bool inherits(const MetaObject* metaObject);
	static STD map<STD string, MetaObject*> metaObjects;
	static MetaObject* getMetaObject(STD string className);
};

#define META_OBJECT		\
public:		\
	static MetaObject metaObject;	\
	virtual MetaObject* getMetaObject() { return &metaObject; }	\
	virtual STD string className(){ return metaObject.className;}	\
	virtual STD string baseClassName() {return metaObject.baseClassName; }	\
	virtual int classID() { return metaObject.classID; }	\
	virtual int baseClassID() { return metaObject.baseClassID; }