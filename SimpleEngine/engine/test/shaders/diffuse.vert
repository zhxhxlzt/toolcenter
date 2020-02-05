#version 420 core
layout (location=0) in vec3 aPos;
layout (location=3) in vec2 aTexCoord;

out vec2 TexCoord;

layout (std140, binding = 0) uniform Matrices
{
	mat4 proj;
	mat4 view;
};

void main()
{
	TexCoord = aTexCoord;
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}