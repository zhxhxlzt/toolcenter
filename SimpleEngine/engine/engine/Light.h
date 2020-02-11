#pragma once
#include "Object.h"
#include "Behaviour.h"
namespace yk
{
	enum class LightType { Spot=0, Directional=1, Point=2};
	class Light : public Behaviour
	{
		META_OBJECT
	public:
		LightType lightType() { return m_lightType; }
		void  setLightType(LightType lightType) { m_lightType = lightType; }
		float spotAngle() { return m_spotAngle; }
		float setSpotAngle(float angle) { m_spotAngle = angle; }
		float intensity() { return m_intensity; }
		void  setIntensity(float i) { m_intensity = i; }
		float range() { return m_range; }
		void  setRange(float far) { m_range = far; }
		vec3  color() { return m_color; }
		void  setColor(vec3 color) { m_color = color; }
	private:
		LightType m_lightType;
		float m_spotAngle;
		float m_range = 100;
		float m_intensity = 1;
		vec3 m_color = vec3{ 1, 1, 1 };
	};
}