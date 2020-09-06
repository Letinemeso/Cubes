//vertex shader
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 inColor;

uniform mat4x4 modelTransf;
uniform mat4x4 perspProjection;

out vec4 Color;

void main(){
	Color = vec4(inColor, 1.0f);

	gl_Position = perspProjection * modelTransf * vec4(position, 1.0f);
}