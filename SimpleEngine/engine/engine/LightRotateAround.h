#pragma once

#include "ykEngine.h"

class LightRotateAround : public MonoBehaviour
{
	META_OBJECT
public:
	SharedPtr<Transform> target;
	void Update() override
	{
		transform()->rotateAround(target->position(), vec3(0, 1, 0), m_anglePerFrame);
	}

private:
	float m_anglePerFrame = 5;
	
};