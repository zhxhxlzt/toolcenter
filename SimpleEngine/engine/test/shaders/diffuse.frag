#version 420 core
out vec4 FragColor;

uniform sampler2D _MainTex;
uniform sampler2D _ShadowMap;
uniform samplerCube _PointShadowMap;

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

struct PointLightInfo
{						// 对齐量		// 偏移量
	vec3 color;			// 16			// 0
	vec3 pos;			// 16			// 16
	float intensity;	// 4			// 32	size ==> 36 ==> 48(填充到vec4的倍数)
};

layout (std140, binding=1) uniform PointLights
{										// 对齐量		// 偏移量
	PointLightInfo	pointLight[10];		// 480			// 0
	int				pointLightCount;	// 4			// 480	size ==> 484
};

struct DirectionalLightInfo
{						// 对齐量	偏移量
	vec3	color;		// 16		0   
	vec3	dir;		// 16		16	 
	vec3	pos;		// 16		32
	float	intensity;	// 4		48		size ==> 52 ==> 64
};

layout (std140, binding=2) uniform DirectLights
{
	DirectionalLightInfo	directLight[10];	// 640,		0		
	int						directLightCount;	// 4		640		size ==> 644	
};


float near = 0.1; 
float far  = 25; 

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

float CalPointShadowFactor(vec3 lightPos)
{
	vec3 lightToFrag = FragPos - lightPos;
	float depth = texture(_PointShadowMap, lightToFrag).r * far;
	float curDepth = length(lightToFrag);
	float shadow = (curDepth - 0.05) > depth ? 1 : 0;
	return shadow;
}

vec4 phongDirectLight(float diff, float spec, vec3 lightColor,
	vec3 norm, vec3 lightDir, vec3 viewDir)
{
	float	diffuse		 = max(dot(norm, lightDir), 0);
	vec3	diffColor	 = diff * diffuse * lightColor;
	vec3	reflectDir	 = reflect(-lightDir, norm);
	float	specular	 = pow(max(dot(reflectDir, viewDir), 0), 32);
	vec3	specColor	 = spec * specular * lightColor;
	float	shadow		 = CalShadowFactor(FragPosLightSpace);
	return vec4((1 - shadow) *(diffColor + specColor), 1);
}

vec4 phongPointLight(float diff, float spec, vec3 lightColor, vec3 lightPos,
					 vec3 norm, vec3 viewDir)
{
	vec3	lightDir	 = normalize(lightPos - FragPos);
	float	diffuse		 = max(dot(norm, lightDir), 0);
	vec3	diffColor	 = diff * diffuse * lightColor;
	vec3	reflectDir	 = reflect(-lightDir, norm);
	float	specular	 = pow(max(dot(reflectDir, viewDir), 0), 32);
	vec3	specColor	 = spec * specular * lightColor;
	float	shadow		 = CalPointShadowFactor(lightPos);
	return vec4((1 - shadow) *(diffColor + specColor), 1);
	//return vec4(diffColor + specColor, 1);	
}


void main()
{
	vec4	objectColor = texture(_MainTex, TexCoord);
	vec4	ambientColor = 0.2 * objectColor;

	vec3	norm		= normalize(Normal);
	vec3	viewDir		= normalize(ViewPos - FragPos);

	if (directLightCount > 0){
		DirectionalLightInfo  l = directLight[0];
		vec3    lightDir	= normalize(-l.dir);
	}
	
	
	//vec4	dirLightColor	= phongDirectLight(1, 1, l.color, norm, lightDir, viewDir);

	PointLightInfo p = pointLight[0];
	vec3	pointDir = FragPos - p.pos;
	float	curDepth = length(pointDir);
	vec4	pointLightColor = phongPointLight(1, 1, p.color, p.pos, norm, viewDir);
	FragColor = pointLightColor * objectColor;
}