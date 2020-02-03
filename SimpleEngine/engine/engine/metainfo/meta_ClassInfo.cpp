/********************************************
此文件由程序自动生成，请勿手动更改
********************************************/

#include<map>
#include<string>
 
#include"MetaObject.h"

// 包含头文件
#include "Application.h"
#include "BaseComponent.h"
#include "Component.h"
#include "GameObject.h"
#include "Input.h"
#include "Mesh.h"
#include "Object.h"
#include "Timer.h"
#include "TimerMgr.h"
#include "Transform.h"
#include "Window.h"

using namespace std;
using namespace yk;
// 元数据字典
map<string, MetaObject*> MetaObject::metaObjects = {
    pair<string, MetaObject*>("Application", &Application::s_metaObject),
	pair<string, MetaObject*>("BaseComponent", &BaseComponent::s_metaObject),
	pair<string, MetaObject*>("Component", &Component::s_metaObject),
	pair<string, MetaObject*>("GameObject", &GameObject::s_metaObject),
	pair<string, MetaObject*>("Input", &Input::s_metaObject),
	pair<string, MetaObject*>("Mesh", &Mesh::s_metaObject),
	pair<string, MetaObject*>("Object", &Object::s_metaObject),
	pair<string, MetaObject*>("Timer", &Timer::s_metaObject),
	pair<string, MetaObject*>("TimerMgr", &TimerMgr::s_metaObject),
	pair<string, MetaObject*>("Transform", &Transform::s_metaObject),
	pair<string, MetaObject*>("Window", &Window::s_metaObject)
};