#version 330
in vec4 color;
in vec4 vertex_position;
uniform vec3 vertex_positions[1024];

void main( void )
{
	vec3 angle_color = vec3(0.0);
	
	//exponents
	float x_squared = pow(vertex_positions[0].x , 2);
	float y_squared = pow(vertex_positions[0].y , 2);
	float z_squared = pow(vertex_positions[0].z , 2);
	
	//addition
	float result_of_xs_ys_zs = x_squared + y_squared + z_squared;
	
  //exponents
	float x_second_squared = pow(vertex_positions[1].x , 2);
	float y_second_squared = pow(vertex_positions[1].y , 2);
	float z_second_squared = pow(vertex_positions[1].z , 2);
	
	//addition
	float result_second_of_xs_ys_zs = x_second_squared + y_second_squared + z_second_squared;
	
	
	//multiply numbers within square root
	float multiply_numbers_within_square_root = result_of_xs_ys_zs * result_second_of_xs_ys_zs;
	
	//square root multiplied numbers
	float bottom_result_of_big_division = sqrt(multiply_numbers_within_square_root);
	
	//cross product
	vec3 cross_product_vec3 = cross(vertex_positions[0], vertex_positions[1]);
	float cross_prosuct_float = cross_product_vec3.x + cross_product_vec3.y + cross_product_vec3.z;
	
	
	//divide top bottom
	float divide_top_bottom = cross_prosuct_float / bottom_result_of_big_division;
	
	
	//cos inverse the result
	float inverse_cos = acos(divide_top_bottom);
	
	//cos 
	float angle_as_radians = cos(inverse_cos);
	
	
	gl_FragColor = vec4(vertex_positions[0].x , vertex_positions[0].y,vertex_positions[0].z , 1.0);
	
	
	//gl_FragColor = color; //vec4(vertex_positions[0], 1.0);
		
}	