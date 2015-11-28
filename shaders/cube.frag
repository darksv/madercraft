#version 330 core

uniform sampler2D faceTexture;

in float globalTime;
in vec2 textureCoords;
in int instanceId;

out vec4 color;

void main()
{
	color = texture(faceTexture, vec2(textureCoords.x, 1.0 - textureCoords.y));// * tan(globalTime * sqrt(textureCoords.x * textureCoords.x + textureCoords.y * textureCoords.y));
}	