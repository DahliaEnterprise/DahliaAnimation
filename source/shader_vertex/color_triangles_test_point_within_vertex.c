#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 incolor;
out vec4 color;
out vec4 vertex_position;

uniform vec3 stoplight_positions[1024];

void main( void )
{
	vec3 new_position = position;
	new_position.x = new_position.x / new_position.z;
	new_position.y = new_position.y / new_position.z;
	
	gl_Position = vec4(position, 1.0);
	
	color = vec4(incolor, 1.0);
	
}
