#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

uniform sampler2D textures[32];

void main()
{
	float intensity = 1.0f / length(fs_in.position.xy - light_pos);
	vec4 texColor = fs_in.color;

	if (fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);
		texColor = vec4(fs_in.color.rgb, 0.0f) + texture(textures[tid], fs_in.uv);
	}

	color = texColor;// * intensity;
}