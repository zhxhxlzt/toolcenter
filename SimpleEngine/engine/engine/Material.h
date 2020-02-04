#pragma once
#include "Object.h"
#include "Shader.h"
namespace yk
{
	class Material : public Object
	{
	public:
		Material(SharedPtr<Shader> shader) : Object(), shader(shader) {}
		SharedPtr<Shader> shader;
	};
}