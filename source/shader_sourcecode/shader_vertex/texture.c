#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texture_position;
out vec4 vertex_position;
out vec2 texture_coordinate;
void main( void )
{
	gl_Position = vec4(position, 1.0);
	texture_coordinate = texture_position;
}
