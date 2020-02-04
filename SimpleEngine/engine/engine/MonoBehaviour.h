#pragma once

#include "Behaviour.h"

namespace yk
{
	class MonoBehaviour : public Behaviour
	{
		META_OBJECT
	public:
		virtual void Awake() {}
		virtual void Start() {}
		virtual void FixedUpdate() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
	};
}