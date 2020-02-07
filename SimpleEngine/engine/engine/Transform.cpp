#include "Transform.h"

using namespace glm;
using namespace yk;

const vec3 Transform::zero = vec3(0, 0, 0);
const vec3 Transform::sforward = vec3(0, 0, -1);
const vec3 Transform::sright = vec3(1, 0, 0);
const vec3 Transform::sup = vec3(0, 1, 0);

vec3& Transform::position() { return m_position; }

vec3& Transform::scale() { return m_scale; }

vec3 Transform::forward() { return m_rotation * sforward; }

vec3 Transform::right() { return m_rotation * sright; }

vec3 Transform::up() { return m_rotation * sup; }

quat Transform::rotation()
{
	return m_rotation;
}

void Transform::rotateAround(vec3 point, vec3 axis, float angle)
{
	angle = radians(angle);
	auto rot = angleAxis(angle, axis);
	auto dir = position() - point;
	auto dis = length(dir);
	auto targetDir = rot * normalize(dir);
	auto targetPos = point + dis * targetDir;
	position() = targetPos;
	auto targetRot = rot * rotation();
	setRotation(targetRot);
}