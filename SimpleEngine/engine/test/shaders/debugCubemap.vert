#version 420 core

layout (location = 0) in vec3 aPos;

out vec3 LocalFragPos;
uniform mat4 model;

layout (std140, binding=0) uniform Matrices
{
	mat4 proj;
	mat4 view;
	mat4 viewPos;
};

void main()
{
	LocalFragPos = aPos;
	gl_Position = proj * view * model * vec4(aPos, 1);
}