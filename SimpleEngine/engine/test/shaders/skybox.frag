#version 420 core
out vec4 FragColor;
in vec3 TexCoord;
uniform samplerCube _SkyBoxA;	// ͨ��renderdoc���Կ�����պ�����
//uniform sampler2D _MainTex;
void main()
{
	//FragColor = texture(_MainTex, abs(TexCoord.xy));
	FragColor = texture(_SkyBoxA, TexCoord);		// �޷������պ���ɫ
}