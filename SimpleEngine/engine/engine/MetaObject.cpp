#include "MetaObject.h"

using namespace yk;

const MetaObject* MetaObject::baseMetaObject()
{
	return getMetaObject(baseClassName);
}

bool MetaObject::inherits(const MetaObject* metaObject)
{
	auto curMetaObject = this;
	while (curMetaObject != nullptr)
	{
		if (curMetaObject->classID == metaObject->classID || curMetaObject->baseClassID == metaObject->classID)
			return true;
		curMetaObject = getMetaObject(curMetaObject->baseClassName);
	}
	return false;
}

MetaObject* MetaObject::getMetaObject(STD string className)
{
	auto result = metaObjects.find(className);
	if (result == metaObjects.cend())
		return nullptr;
	else
		return metaObjects[className];
}