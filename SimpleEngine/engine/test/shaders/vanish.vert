#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 3) in vec2 aTexCoord;

out VS_OUT
{
	vec3 normal;
	vec2 texCoord;
} vs_out;

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
	mat3 normalMatrix = mat3(transpose(inverse(view * model)));
	vs_out.normal = normalize(vec3(proj * vec4(normalMatrix * aNormal, 0.0)));
	vs_out.texCoord = aTexCoord;
}