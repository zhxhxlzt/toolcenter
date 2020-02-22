#pragma once
#include "MonoBehaviour.h"
using namespace yk;

class CtrlBoom : public MonoBehaviour
{
	META_OBJECT;
public:
	float distance=1;
	float begin = 0;
	void Update() override;
};