
precision highp float;

out vec4 frag_color;

in vec2 vertex_texture;

void main() {

	vec2 offset = vertex_texture - 0.5;

	float distance = sqrt(dot(offset, offset));

	if(distance > 0.2)

		discard;
	
	frag_color = vec4(

		vertex_texture.y, 
		0.6, 
		(vertex_texture.y * 0.5) + 0.5,

		1.0

	) * 1.4;

}
