#version 440 core

layout(location = 0) out vec4 texelColor;

uniform sampler2D windowBuffer;
in vec2 texelCoords;

void main()
{
	texelColor = texture(windowBuffer, texelCoords);
}
