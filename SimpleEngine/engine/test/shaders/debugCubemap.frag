#version 420 core

in vec3 LocalFragPos;
uniform samplerCube _PointShadowMap;

void main()
{
	float d = texture(_PointShadowMap, LocalFragPos).r;
	gl_FragColor = vec4(vec3(d), 1);
}