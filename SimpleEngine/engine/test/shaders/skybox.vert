#version 420 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoord;
layout (std140, binding = 0) uniform Matrices
{
	mat4 proj;
	mat4 view;
	vec3 viewPos;
};

void main()
{
	TexCoord = aPos;
	mat4 viewNoMove = mat4(mat3(view));
	vec4 pos = proj * viewNoMove * vec4(aPos, 1);
	gl_Position = pos.xyww;
}