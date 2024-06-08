#version 440 core

layout(location = 0) in vec2 _vertexPos;
layout(location = 1) in vec2 _texelCoords;

out vec2 texelCoords;

void main() 
{
	texelCoords = _texelCoords;
	gl_Position = vec4(_vertexPos, 0.0, 1.0);
}
