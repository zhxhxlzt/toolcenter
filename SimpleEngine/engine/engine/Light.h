#pragma once
#include "Object.h"
#include "Behaviour.h"

namespace yk
{
	class Light : public Behaviour
	{
		META_OBJECT
	public:
		vec3 position;
	};
}