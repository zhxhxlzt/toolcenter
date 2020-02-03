#pragma once
#include <map>
#include <string>
#define STD std::

namespace yk
{
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
}

#define META_OBJECT		\
public:		\
	friend struct MetaObject;	\
	static MetaObject* metaObject(){ return &s_metaObject; }	\
	virtual MetaObject* getMetaObject() { return &s_metaObject; }	\
	virtual STD string className(){ return s_metaObject.className;}	\
	virtual STD string baseClassName() {return s_metaObject.baseClassName; }	\
	virtual int classID() { return s_metaObject.classID; }	\
	virtual int baseClassID() { return s_metaObject.baseClassID; }	\
private:	\
	static MetaObject s_metaObject;	\
