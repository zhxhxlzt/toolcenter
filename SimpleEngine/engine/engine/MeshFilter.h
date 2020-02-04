#pragma once

#include <Component.h>
#include <Mesh.h>

namespace yk
{
	class MeshFilter : public Component
	{
		META_OBJECT
	public:
		SharedPtr<Mesh> sharedMesh;
	};
}