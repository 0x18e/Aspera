#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 tex_coords;
out vec3 c;
out vec2 texture_coordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	texture_coordinates = tex_coords;
	c = col;
	gl_Position = projection * view * model * vec4(pos, 1.0);
}