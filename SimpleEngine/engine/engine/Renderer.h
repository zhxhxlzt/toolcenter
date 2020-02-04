#pragma once
#include "Component.h"
#include "Material.h"
namespace yk
{
	class Renderer : public Component
	{
		META_OBJECT
	public:
		bool enabled = true;
		STD vector<SharedPtr<Material>> materials;
		SharedPtr<Material> material;
	private:
		friend class RenderMgr;
		virtual void rendering() {}
	};
}