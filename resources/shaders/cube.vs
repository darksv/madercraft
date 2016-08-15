#version 330 core

#extension GL_ARB_explicit_uniform_location : require
#extension GL_ARB_separate_shader_objects : require

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 textureCoords_;
layout (location = 2) in mat4 modelMatrix;

layout (location = 0) uniform float globalTime_;
layout (location = 1) uniform mat4 viewMatrix;
layout (location = 2) uniform mat4 projectionMatrix;

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
