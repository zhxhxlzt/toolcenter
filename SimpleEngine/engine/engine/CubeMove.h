#pragma once
#include "ykEngine.h"

using namespace yk;


class CubeMove : public MonoBehaviour
{
	META_OBJECT
public:
	void Update() override
	{
		transform()->rotate(3, vec3(0, 1, 0));
	}
};