#version 420 core
out vec4 FragColor;
in vec3 TexCoord;
uniform samplerCube _SkyBoxA;	// 通过renderdoc可以看到天空盒数据
//uniform sampler2D _MainTex;
void main()
{
	//FragColor = texture(_MainTex, abs(TexCoord.xy));
	FragColor = texture(_SkyBoxA, TexCoord);		// 无法釆样天空盒颜色
}