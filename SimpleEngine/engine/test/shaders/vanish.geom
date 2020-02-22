#version 420 core

layout (triangles) in;
layout (triangle_strip, max_vertices=3) out;

uniform float progress;
uniform float vanishDis;

in VS_OUT
{
	vec3 normal;
	vec2 texCoord;
} gs_in[];

out vec2 TexCoord;

vec4 explode(vec4 position, vec3 normal, float p, float v)
{
    vec3 direction = progress * vanishDis * normal; 
	//vec3 direction = normal;
    return position + vec4(direction, 0.0);
}

void main()
{
	for (int i = 0; i < 3; i++)
	{
		gl_Position = explode(gl_in[i].gl_Position, gs_in[i].normal, progress, vanishDis);
		//gl_Position = gl_in[i].gl_Position;
		TexCoord = gs_in[i].texCoord;
		EmitVertex();
	}
	EndPrimitive();
}

