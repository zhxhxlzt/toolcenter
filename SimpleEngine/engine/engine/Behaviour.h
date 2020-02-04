#pragma once
#include "Component.h"

namespace yk
{
	class Behaviour : public Component
	{
		META_OBJECT
	public:
		Behaviour() : Component() {}
		bool enabled = true;
	};
}