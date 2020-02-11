#version 420 core

layout (location=0) in vec3 aPos;

uniform mat4 model;
layout (std140, binding = 0) uniform Matrices
{
	mat4 proj;
	mat4 view;
	vec3 viewPos;
};

void main()
{
	gl_Position = proj * view * model * vec4(aPos, 1);
}