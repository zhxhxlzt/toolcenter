#version 420 core
out vec4 FragColor;

uniform sampler2D _MainTex;
uniform sampler2D _ShadowMap;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 directLightDir;
in vec3 ViewPos;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosLightSpace;

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

struct DirectionalLight
{						// 对齐量	偏移量
	float	intensity;	// 4		0
	vec3	color;		// 16		16   <-- 4	必需是对齐量的位数
	vec3	dir;		// 16		32	 size ===> 48
};

layout (std140, binding=2) uniform DirectLights
{
	DirectionalLight	directLight[10];	// 480,		0
	int				count;				// 4		484		size ===> 488
};



float near = 0.1; 
float far  = 10.0; 

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));    
}

float CalShadowFactor(vec4 lightSpaceCoord)
{
	vec3	projCoords = lightSpaceCoord.xyz / lightSpaceCoord.w;
	projCoords = projCoords * 0.5 + 0.5;
	float	closetDepth = texture(_ShadowMap, projCoords.xy).r;
	float	curDepth	= projCoords.z;
	if (curDepth > 1.0f)
		return 0.0f;
	float	shadow		= curDepth - 0.005 > closetDepth ? 1.0f : 0.0f;
	return shadow;
}

vec4 phongDirectLight( 
	float ambient, float diff, float spec, vec3 lightColor,
	vec3 norm, vec3 lightDir, vec3 viewDir)
{
	vec3	ambientColor = ambient * lightColor;
	float	diffuse		 = max(dot(norm, lightDir), 0);
	vec3	diffColor	 = diff * diffuse * lightColor;
	vec3	reflectDir	 = reflect(-lightDir, norm);
	float	specular	 = pow(max(dot(reflectDir, viewDir), 0), 32);
	vec3	specColor	 = spec * specular * lightColor;
	float	shadow		 = CalShadowFactor(FragPosLightSpace);
	return vec4(ambientColor + (1 - shadow) *(diffColor + specColor), 1);
	return vec4(diffuse * diffColor, 1);
	return vec4(lightDir, 1);
}




void main()
{
	DirectionalLight  l = directLight[0];
	vec3	norm		= normalize(Normal);
	vec3    lightDir	= normalize(-l.dir);

	vec3	viewDir		= normalize(ViewPos - FragPos);
	vec4	phongColor	= phongDirectLight(0.3, 1, 1, l.color, norm, lightDir, viewDir);

	vec4	objectColor = texture(_MainTex, TexCoord);
	
	FragColor = phongColor * objectColor;
	
	//vec4	dep	= texture(_ShadowMap, TexCoord);
	//FragColor	= vec4(vec3(dep.r), 1.0);
}