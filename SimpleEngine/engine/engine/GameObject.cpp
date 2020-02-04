#include "GameObject.h"
#include "Transform.h"

using namespace std;
using namespace yk;
GameObject::GameObject()
{
	m_transform = make_shared<Transform>();
}

shared_ptr<Transform> GameObject::transform()
{
	return m_transform;
}