/********************************************
此文件由程序自动生成，请勿手动更改
********************************************/

#include<map>
#include<string>
 
#include"MetaObject.h"

// 包含头文件
#include "BaseComponent.h"
#include "Component.h"
#include "Object.h"
#include "Timer.h"
#include "Transform.h"
#include "World.h"

using namespace std;
// 元数据字典
map<string, MetaObject*> MetaObject::metaObjects = {
    pair<string, MetaObject*>("BaseComponent", &BaseComponent::s_metaObject),
	pair<string, MetaObject*>("Component", &Component::s_metaObject),
	pair<string, MetaObject*>("Object", &Object::s_metaObject),
	pair<string, MetaObject*>("Timer", &Timer::s_metaObject),
	pair<string, MetaObject*>("Transform", &Transform::s_metaObject),
	pair<string, MetaObject*>("World", &World::s_metaObject)
};