#pragma once

#include "MonoBehaviour.h"
#include "Transform.h"

using namespace yk;

class AlwaysLookAt : public MonoBehaviour
{
	META_OBJECT
public:
	SharedPtr<Transform> target;
	void LateUpdate() override
	{
		transform()->LookAt(target->position());
		//cout << "targetPos:" << target->position() << endl;
	}
};