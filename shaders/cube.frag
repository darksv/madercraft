#version 330 core

in vec2 textureCoord;
in float globalTime;

out vec4 color;
uniform float time;
uniform sampler2D ourTexture;

void main()
{
	color = texture(ourTexture, vec2(textureCoord.x, 1.0 - textureCoord.y)) * sin(globalTime * gl_InstanceID);
}	