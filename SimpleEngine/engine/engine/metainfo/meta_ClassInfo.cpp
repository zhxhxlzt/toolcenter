/********************************************
���ļ��ɳ����Զ����ɣ������ֶ�����
********************************************/

#include<map>
#include<string>
 
#include"MetaObject.h"

// ����ͷ�ļ�
#include "BaseComponent.h"
#include "Component.h"
#include "Delegate.h"
#include "GameObject.h"
#include "Object.h"
#include "Timer.h"
#include "Transform.h"
#include "World.h"

using namespace std;
// Ԫ�����ֵ�
map<string, MetaObject*> MetaObject::metaObjects = {
    pair<string, MetaObject*>("BaseComponent", &BaseComponent::metaObject),
	pair<string, MetaObject*>("Component", &Component::metaObject),
	pair<string, MetaObject*>("GameObject", &GameObject::metaObject),
	pair<string, MetaObject*>("Object", &Object::metaObject),
	pair<string, MetaObject*>("Timer", &Timer::metaObject),
	pair<string, MetaObject*>("Transform", &Transform::metaObject),
	pair<string, MetaObject*>("World", &World::metaObject)
};