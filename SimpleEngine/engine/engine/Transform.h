#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
using namespace std;
namespace yk
{
	using namespace glm;
	using namespace std;
	class Transform : public Component
	{
		META_OBJECT
	private:
		// 本地空间
		vec3 m_position;
		vec3 m_scale;
		qua<float> m_rotation;

		static const vec3 zero;
		static const vec3 sforward;
		static const vec3 sright;
		static const vec3 sup;

	public:
		Transform() : Component(),
			m_position(vec3(.0f, .0f, .0f)),
			m_scale(vec3(1.0f, 1, 1))
		{
			m_rotation = qua<float>(mat4(1));
		}

		void translate(vec3 moveVec)
		{
			m_position += moveVec;
		}

		void MoveTo(vec3 destPos)
		{
			m_position = destPos;
		}

		void rotate(float angle, vec3 axis)
		{
			angle = radians(angle);
			auto q = angleAxis(angle, axis);
			auto rot = q * m_rotation;
			setRotation(rot);
		}

		void setRotation(qua<float>& rot)
		{
			m_rotation = rot;
		}

		void LookAt(vec3 targetPos)
		{
			auto from = forward();
			auto to = targetPos - position();
			auto rot0 = fromToRotation(from, to);
			
			vec3 right = glm::cross(to, vec3(0, 1, 0));
			vec3 targetUp = glm::cross(right, to);

			vec3 oldUp = up();
			vec3 newUp = rot0 * up();
			auto rot1 = fromToRotation(newUp, targetUp);	// 调整up向量

			auto rot = rot1 * rot0 * m_rotation;
			setRotation(rot);
		}

		quat fromToRotation(vec3 from, vec3 to)
		{
			from = normalize(from);
			to = normalize(to);
			auto cosTheta = dot(from, to);
			vec3 rotAxis;
			if (cosTheta < -1 + 0.001f)
			{
				rotAxis = cross(vec3(0.0f, 0.0f, 1.0f), from);
				if (length2(rotAxis) < 0.01)
					rotAxis = cross(vec3(1.0f, 0.0f, 0.0f), from);
				rotAxis = normalize(rotAxis);
				return angleAxis(180.0f, rotAxis);
			}
			if (cosTheta > 0.99999f)
			{
				return quat(1, 0, 0, 0);
			}
			auto radius = acos(cosTheta);
			auto angle = radius * 180 / pi<float>();
			
			rotAxis = cross(from, to);
			return angleAxis(radius, normalize(rotAxis));
		}

		mat4 View()
		{
			return glm::lookAt(m_position, m_position + forward(), up());
		}

		mat4 Model()
		{
			mat4 model(1);
			model = glm::translate(model, m_position);
			model = glm::scale(model, m_scale);
			model *= mat4_cast(m_rotation);
			return model;
		}

		vec3& position();

		vec3& scale();

		quat rotation();

		vec3 forward();

		vec3 right();

		vec3 up();


		void debug()
		{
			cout << "-----------------transform-------------------" << endl;
			cout << "position:" << transform()->position() << endl;
			cout << "scale:   " << transform()->scale() << endl;
			cout << "rotation:" << transform()->rotation() << endl;
		}

		~Transform()
		{
			cout << "tr d" << endl;
		}
	};
}