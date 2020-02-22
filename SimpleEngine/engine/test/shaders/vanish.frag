#version 420 core

out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D _MainTex;

in VS_OUT
{
	vec3 normal;
	vec2 texCoord;
} fs_in;

void main()
{
	FragColor = texture(_MainTex, TexCoord);
	//FragColor = texture(_MainTex, fs_in.texCoord);
}