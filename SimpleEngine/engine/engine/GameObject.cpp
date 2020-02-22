#include "GameObject.h"
#include "Transform.h"
#include "SceneMgr.h"
#include "Renderer.h"
#include "MonoBehaviour.h"
#include "Light.h"
#include "SkyBox.h"
#include "ScriptMgr.h"
using namespace std;
using namespace yk;

SharedPtr<GameObject> GameObject::create() {
	auto gb = make_shared<GameObject>();
	auto tr = gb->addComponent<Transform>();

	auto scene = SceneMgr::getCurrentScene();
	scene->addRootGameObject(gb);
	return gb;
}

shared_ptr<Transform> GameObject::transform()
{
	return getComponent<Transform>();
}

void GameObject::checkAddComponent(STD shared_ptr<Component> comp)
{
	auto metaObj = comp->getMetaObject();
	auto scene = SceneMgr::getCurrentScene();
	if (metaObj->inherits(MetaObject::getMetaObject("Camera")))
	{
		if (scene->mainCamera == nullptr)
		{
			scene->mainCamera = static_pointer_cast<Camera>(comp);
		}
	}
	else if (metaObj->inherits(MetaObject::getMetaObject("Renderer")))
	{
		scene->AddRenderer(static_pointer_cast<Renderer>(comp));
	}
	else if (metaObj->inherits(MetaObject::getMetaObject("MonoBehaviour")))
	{
		auto mb = static_pointer_cast<MonoBehaviour>(comp);
		mb->Awake();
		//scene->AddMonoBehaviour(mb);
		ScriptMgr::addNewMonoBehaviours(mb);
	}
	else if (metaObj->inherits(MetaObject::getMetaObject("Light")))
	{
		auto lt = static_pointer_cast<Light>(comp);
		scene->AddLight(lt);
	}
	else if (metaObj->inherits(MetaObject::getMetaObject("SkyBox")))
	{
		auto skyBox = static_pointer_cast<SkyBox>(comp);
		scene->skyBox = skyBox;
	}
}

void GameObject::checkDelComponent(STD shared_ptr<Component> comp)
{
	auto metaObj = comp->getMetaObject();
	auto scene = SceneMgr::getCurrentScene();
	if (metaObj->inherits(MetaObject::getMetaObject("Renderer")))
	{
		scene->DelRenderer(static_pointer_cast<Renderer>(comp));
	}
	else if (metaObj->inherits(MetaObject::getMetaObject("MonoBehaviour")))
	{
		scene->DelMonoBehaviour(static_pointer_cast<MonoBehaviour>(comp));
	}
}

