//vertex shader
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 inColor;

uniform mat4x4 projection;
uniform mat4x4 move;
uniform mat4x4 rotate;
uniform mat4x4 size;

uniform mat4x4 modelTransf;
uniform mat4x4 perspProjection;

out vec4 Color;

void main(){
	Color = vec4(inColor, 1.0f);

	/*gl_Position = projection * move * rotate * (perspProjection * (modelTransf * vec4(position, 1.0f)));*/

	vec4 v = vec4(position, 1.0f);
	vec4 newPos = modelTransf * v;
	vec4 projPos = perspProjection * newPos;


	gl_Position = move * rotate * projPos;
	//gl_Position = rotate * vec4(position, 1.0f);
}