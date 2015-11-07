#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec4 Color;

uniform mat4 gWorld;

out vec4 oColor;

void main()
{
	gl_Position = vec4(Position, 1.0) * gWorld;
	oColor = Color;
}