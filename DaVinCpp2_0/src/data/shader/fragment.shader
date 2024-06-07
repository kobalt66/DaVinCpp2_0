#version 420 core

out vec4 texelColor;

uniform sampler2D windowBuffer;
in vec2 texelPos;

void main()
{
	texelColor = texture(windowBuffer, texelPos);
}
