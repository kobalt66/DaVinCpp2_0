#version 420 core

layout(location=0) in vec2 vertexPos;

out vec2 texelPos;

void main() 
{
	texelPos = vertexPos;
	gl_Position = vec4(vertexPos, 0.0, 1.0);
}
