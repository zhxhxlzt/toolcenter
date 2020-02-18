#pragma once

#include "Behaviour.h"
#include "FrameBuffer.h"

namespace yk
{
	class Camera : public Behaviour
	{
		META_OBJECT
	public:
		bool enablePostEffect = false;
		float fov() {}
		float far() {}
		float near() {}
		void setFov(float fov) { m_fov = fov; }
		void setNear(float near) { m_near = near; }
		void setFar(float far) { m_far = far; }

		mat4 Proj()
		{
			return perspective(45.0f, 800.0f / 600, m_near, m_far);
		}

		unsigned int GetCullingMask() { return m_cullingMask; }
		FrameBuffer& getShadowFrameBuffer() { return m_shadowBuffer; }
		FrameBuffer& getPointShadowFrameBuffer() { return m_pointShadowBuffer; }

	private:
		float m_fov = 45.0f;
		float m_near = 0.1f;
		float m_far = 1000.0f;
		unsigned int m_cullingMask;
		FrameBuffer m_shadowBuffer;
		FrameBuffer m_pointShadowBuffer;
	};
}