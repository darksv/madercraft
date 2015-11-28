#version 330 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 textureCoords_;
layout (location = 2) in mat4 modelMatrix;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float globalTime_;

out float globalTime;
out vec2 textureCoords;
out int instanceId;

void main()
{
	globalTime = globalTime_;
	textureCoords = textureCoords_;
	instanceId = gl_InstanceID;

	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
}