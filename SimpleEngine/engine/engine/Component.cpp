#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
using namespace yk;

STD shared_ptr<Transform> Component::transform() {
	return gameObject()->getComponent<Transform>();
}