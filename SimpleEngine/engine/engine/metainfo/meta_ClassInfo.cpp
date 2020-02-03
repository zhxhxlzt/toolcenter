/********************************************
���ļ��ɳ����Զ����ɣ������ֶ�����
********************************************/

#include<map>
#include<string>
 
#include"MetaObject.h"

// ����ͷ�ļ�
#include "Application.h"
#include "BaseComponent.h"
#include "Component.h"
#include "Object.h"
#include "TimerMgr.h"
#include "Transform.h"

using namespace std;
// Ԫ�����ֵ�
map<string, MetaObject*> MetaObject::metaObjects = {
    pair<string, MetaObject*>("Application", &Application::s_metaObject),
	pair<string, MetaObject*>("BaseComponent", &BaseComponent::s_metaObject),
	pair<string, MetaObject*>("Component", &Component::s_metaObject),
	pair<string, MetaObject*>("Object", &Object::s_metaObject),
	pair<string, MetaObject*>("TimerMgr", &TimerMgr::s_metaObject),
	pair<string, MetaObject*>("Transform", &Transform::s_metaObject)
};