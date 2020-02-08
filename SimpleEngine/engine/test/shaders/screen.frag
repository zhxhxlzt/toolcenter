#version 420 core

in vec2 TexCoord;
uniform sampler2D _ShadowMap;

out vec4 FragColor;
void main()
{
	float dep = texture(_ShadowMap, TexCoord).r;
	FragColor = vec4(vec3(dep), 1);
}