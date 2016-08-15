#version 330 core

#extension GL_ARB_explicit_uniform_location : require
#extension GL_ARB_separate_shader_objects : require

 in float globalTime;
 in vec2 textureCoords;
 in int instanceId;

uniform sampler2D faceTexture;

out vec4 color;

void main()
{
	color = texture(faceTexture, vec2(textureCoords.x, 1.0 - textureCoords.y));
}
