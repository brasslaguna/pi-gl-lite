
precision highp float;

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texture;

out vec2 vertex_texture;

void main() {

	vertex_texture = texture;

	gl_Position = vec4(position, 1.0);

}
