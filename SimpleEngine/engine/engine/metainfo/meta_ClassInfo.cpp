/********************************************
���ļ��ɳ����Զ����ɣ������ֶ�����
********************************************/

#include<map>
#include<string>
 
#include"MetaObject.h"

// ����ͷ�ļ�
#include "BaseComponent.h"
#include "Component.h"
#include "Object.h"
#include "Timer.h"
#include "Transform.h"
#include "World.h"

using namespace std;
// Ԫ�����ֵ�
map<string, MetaObject*> MetaObject::metaObjects = {
    pair<string, MetaObject*>("BaseComponent", &BaseComponent::s_metaObject),
	pair<string, MetaObject*>("Component", &Component::s_metaObject),
	pair<string, MetaObject*>("Object", &Object::s_metaObject),
	pair<string, MetaObject*>("Timer", &Timer::s_metaObject),
	pair<string, MetaObject*>("Transform", &Transform::s_metaObject),
	pair<string, MetaObject*>("World", &World::s_metaObject)
};