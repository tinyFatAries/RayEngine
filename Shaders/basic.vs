#version 330

layout (location = 0) in vec3 Position;

uniform mat4 gWorld;

void main()
{
	gl_Position = vec4(Position, 1.0) * gWorld;
}