#version 330
in vec4 color;
in vec4 vertex_position;
in vec3 vertex_positions_one;
uniform vec4 ucolor;

void main( void )
{
	/*vec3 point_to_test = vec3(vertex_position);
	
	//vec4 color = vec4(1.0, 0.0, 0.0, 1.0);
	vec4 color_two = vec4(0.0, 1.0, 0.0, 1.0);
	
	float angle_one = acos(dot(normalize(point_to_test), normalize(vec3(vertex_positions[0]))));
	float angle_two = acos(dot(normalize(point_to_test), normalize(vec3(vertex_positions[1]))));
	float angle_three = acos(dot(normalize(point_to_test), normalize(vec3(vertex_positions[2]))));
	
	if(((angle_one + angle_two + angle_three)*1000000) >= (6*1000000))
	{
		gl_FragColor = color_two;
	}else{
		gl_FragColor = color;
	}
	gl_FragColor = vec4(vertex_positions[0], 1.0);*/
	
	
	
		gl_FragColor = ucolor;
		
}	