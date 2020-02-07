#version 420 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNorm;
layout (location=3) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec3 ViewPos;

uniform mat4 model;
layout (std140, binding = 0) uniform Matrices
{
	mat4 proj;
	mat4 view;
	vec3 viewPos;
};

void main()
{
	ViewPos = viewPos;
	TexCoord = aTexCoord;
	Normal = mat3(transpose(inverse(model))) * aNorm;
	FragPos = aPos;
	gl_Position = proj * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}