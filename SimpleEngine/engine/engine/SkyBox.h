#pragma once

#include<Behaviour.h>
#include<Material.h>
namespace yk
{
	class SkyBox : public Behaviour
	{
		META_OBJECT;
	public:
		SharedPtr<Material> material;
	};
}