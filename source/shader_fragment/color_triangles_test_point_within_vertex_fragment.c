#version 330
in vec4 color;
in vec4 vertex_position;
uniform vec3 stoplight_positions[1024];


void main( void )
{
	//translate frag coord position to opengl coordinates
	vec3 fragcoord_as_openglcoordspace = vec3((gl_FragCoord.x/800)-0.5, (gl_FragCoord.y/600)-0.5, gl_FragCoord.z);
	
	vec4 nolight = vec4(0.0, 0.0, 0.0, 1.0);
	
	vec3 light_position = vec3(0.0, 0.0, 0.2);
	
	vec3 current_test_position = vec3(gl_FragCoord);
	
	float dis = distance(current_test_position, light_position);
	
	float ray_hittest_ballsize = 0.5;
	
	float total_hittest_balls = ceil(dis / ray_hittest_ballsize);
	
	float x_step = abs(light_position.x-current_test_position.x) / total_hittest_balls;
	float y_step = abs(light_position.y-current_test_position.y) / total_hittest_balls;
	float z_step = abs(light_position.z-current_test_position.z) / total_hittest_balls;
	
	/*
	
	int ran_into_stoplight_ball = 0;
 float index = 0;
	while((index*1000000) < (total_hittest_balls*1000000))
	{
		if((distance(current_test_position, stoplight_positions[0])*1000000) < (ray_hittest_ballsize*1000000))
		{
			ran_into_stoplight_ball = 1;
			index = total_hittest_balls;
		}
		
		//next
		float current_x_distance = abs(current_test_position.x - light_position.x);
		float distance_after_addition_x = (current_test_position.x+x_step);
		if(distance_after_addition_x > current_x_distance)
		{
			//subtract to get closer to frag
			current_test_position.x = current_test_position.x - x_step;
		}else{
			current_test_position.x = current_test_position.x + x_step;
			
		}
		
		float current_y_distance = abs(current_test_position.y - light_position.y);
		float distance_after_addition_y = (current_test_position.y+y_step);
		if(distance_after_addition_y > current_y_distance)
		{
			//subtract to get closer to frag
			current_test_position.y = current_test_position.y - y_step;
		}else{
			current_test_position.y = current_test_position.y + y_step;
		}
		
		float current_z_distance = abs(current_test_position.z - light_position.z);
		float distance_after_addition_z = (current_test_position.z+z_step);
		if(distance_after_addition_z > current_z_distance)
		{
			//subtract to get closer to frag
			current_test_position.z = current_test_position.z - z_step;
		}else{
			current_test_position.z = current_test_position.z + z_step;
		}
		
		
		
		index = index + 1;
	}
	*/
	//temporary
	int ran_into_stoplight_ball = 0;
	vec3 center_of_triangle = vec3(0.0, 0.0, 0.0);
	float distance_from_center = distance(fragcoord_as_openglcoordspace, center_of_triangle);
	
	float total_slices = 1000000;
	float light_intensity[3];
	float light_distance[3];
	light_intensity[0] = 0.0;
	light_distance[0] = 0.0;
	light_intensity[1] = 0.5;
	light_distance[1] = 0.5;
	light_intensity[2] = 1.0;
	light_distance[2] = 0.8;
	
	//index zero to index one.
	float light_intensity_range = (light_intensity[1] - light_intensity[0]);
	float light_distance_range = (light_distance[1] - light_distance[0]);
	
	float light_intensity_step = light_intensity_range / total_slices;
	float light_distance_step = light_distance_range / total_slices;
	
	//index one to index two

	gl_FragColor = mix(vec4(0.5, 0.0, 0.0, 0.0), nolight,  distance_from_center);
	//gl_FragColor = vec4(distance_from_center , 0.0, 0.0, 1.0);
	
	
	//gl_FragColor = vec4(distance_from_center, (gl_FragCoord.x/800), (gl_FragCoord.y/600), 1.0);
	//gl_FragColor = vec4((gl_FragCoord.x/800), (gl_FragCoord.y/600), 0.0, 1.0);
}	








