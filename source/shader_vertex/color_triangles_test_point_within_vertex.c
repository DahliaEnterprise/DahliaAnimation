#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 incolor;
out vec4 color;
out vec4 vertex_position;

uniform vec3 stoplight_positions[1024];
uniform vec3 offset_position_rotation[2];

void main( void )
{
	vec3 new_position = position;
	
	//translate position
	new_position.x += offset_position_rotation[0].x;
	new_position.y += offset_position_rotation[0].y;
	new_position.z += offset_position_rotation[0].z;
	
	
	//apply depth perspective
	//new_position.x = new_position.x / new_position.z;
	//new_position.y = new_position.y / new_position.z;
	
	gl_Position = vec4(new_position, 1.0);
	
	color = vec4(incolor, 1.0);
	
}
