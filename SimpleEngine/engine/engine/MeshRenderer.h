#pragma once
#include "Renderer.h"
#include "Transform.h"
#include "MeshFilter.h"
namespace yk
{
	class MeshRenderer : public Renderer
	{
		META_OBJECT
	public:

	private:
		friend class RenderMgr;
		void rendering(SharedPtr<Shader> shader=nullptr) override;
	};

}