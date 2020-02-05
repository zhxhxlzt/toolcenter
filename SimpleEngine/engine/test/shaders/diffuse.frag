#version 420 core
out vec4 FragColor;

uniform sampler2D _MainTex;

in vec2 TexCoord;

void main()
{
	FragColor = texture(_MainTex, TexCoord);
}