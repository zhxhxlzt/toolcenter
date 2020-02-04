#include "GameObject.h"
#include "Transform.h"
#include "SceneMgr.h"
using namespace std;
using namespace yk;
GameObject::GameObject()
{
	m_transform = make_shared<Transform>();
}

GameObject::~GameObject()
{
}

SharedPtr<GameObject> GameObject::create() {
	auto gb = make_shared<GameObject>();
	auto scene = SceneMgr::getCurrentScene();
	scene->addRootGameObject(gb);
	return gb;
}
shared_ptr<Transform> GameObject::transform()
{
	return m_transform;
}