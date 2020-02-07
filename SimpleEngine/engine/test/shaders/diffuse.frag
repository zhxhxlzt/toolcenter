#version 420 core
out vec4 FragColor;

uniform sampler2D _MainTex;
uniform vec3 lightColor;
uniform vec3 lightPos;
in vec3 ViewPos;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material
{
	sampler2D albedo;
	sampler2D metalic;
	sampler2D normalMap;
	float	  smoothless;
};

layout (std140, binding=1) uniform PointLights
{
	vec3	light;
};

void main()
{
	float ambient = 0.1;
	vec3 ambientColor	= ambient * lightColor;

	vec3	norm		= normalize(Normal);
	vec3	lightDir	= normalize(light - FragPos);
	float	diff		= max(dot(norm, lightDir), 0);
	vec3	diffColor	= diff * lightColor;

	float	specular = 0.5;
	vec3	viewDir		= normalize(ViewPos - FragPos);
	vec3	reflectDir	= reflect(-lightDir, norm);
	float	spec		= pow(max(dot(reflectDir, viewDir), 0), 32);
	vec3	specColor	= spec * specular * lightColor;

	vec4	objectColor = texture(_MainTex, TexCoord);
	vec3	result		= ambientColor + diffColor + specColor;
	
	FragColor 			= vec4(result, 1) * objectColor;
	//FragColor = vec4(light, 1);
}