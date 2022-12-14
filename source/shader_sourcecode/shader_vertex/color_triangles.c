#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 incolor;
out vec4 color;
out vec4 vertex_position;
void main( void )
{
	gl_Position = vec4(position, 1.0);
	color = vec4(incolor, 1.0);
	vertex_position = vec4(position, 1.0);
}
