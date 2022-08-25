#version 330
in vec4 color;
in vec4 vertex_position;
uniform vec3 stoplight_positions[1024];


void main( void )
{
	//translate frag coord position to opengl coordinates
	//todo: dynamically generate this shader to have hardcoded printed values of screen width(800) and screen height(600).
	vec3 fragcoord_as_openglcoordspace = vec3((gl_FragCoord.x/800)-0.5, (gl_FragCoord.y/600)-0.5, gl_FragCoord.z);
	
	//color for absent of light.
	vec4 nolight = vec4(0.0, 0.0, 0.0, 1.0);
	
	//position of light (white lights reval the object color).
	vec3 light_position = vec3(0.0, 0.0, 0.0);
	
	//position of fragment.
	vec3 current_test_position = fragcoord_as_openglcoordspace;
	
	//get distance from light
		//gradient associated values.
		int total_ranges = 2;
		float light_distance[2];
		float light_intensity[2];
		
		light_distance[0] = 0.7;
		light_intensity[0] = 0.65;
		
		light_distance[1] = 0.3;
		light_intensity[1] = 1.0;
		
		//get distance
		float dis = distance(current_test_position, light_position);
		
		//does distance fit within this range?
		if((dis * 1000000) < (light_distance[0]*1000000))
		{
			float stageone_light_distance = light_distance[0];
			float stageone_light_intensity = light_intensity[0];
			float stageone_resolution = 1000000;
			float stageone_light_intensity_per_one_resolution = stageone_light_intensity / stageone_resolution;
			float stageone_steps_of_light_distance = stageone_light_distance / stageone_resolution;
			
			float stageone_total_sync_steps = dis / stageone_steps_of_light_distance;
			
			float stageone_final_light_intensity = stageone_light_intensity_per_one_resolution * stageone_total_sync_steps;
			
			float final_light_intensity = stageone_final_light_intensity;
			
			gl_FragColor = mix(color, nolight, final_light_intensity);
			
		}else{
			float accumulative_distance = light_distance[0];
			float accumulative_intensity = light_intensity[0];
			int range_found = 0;
			int index = 1;
			while(index < total_ranges)
			{
				if((dis * 1000000) >= accumulative_distance 
				&& (dis * 1000000) < ((accumulative_distance+light_distance[index]) * 1000000))
				{
					range_found = 1;
					index = total_ranges;
					
					float stageone_light_distance = light_distance[index];
					float stageone_light_intensity = light_intensity[index];
					float stageone_resolution = 1000000;
					float stageone_light_intensity_per_one_resolution = stageone_light_intensity / stageone_resolution;
					float stageone_steps_of_light_distance = stageone_light_distance / stageone_resolution;
					
					float stageone_total_sync_steps = (dis-accumulative_distance) / stageone_steps_of_light_distance;
					
					float stageone_final_light_intensity = stageone_light_intensity_per_one_resolution * stageone_total_sync_steps;
					
					
					
					float final_light_intensity = stageone_final_light_intensity + accumulative_intensity;
					
					
					gl_FragColor = mix(color, nolight, final_light_intensity);
					
				}
				
				accumulative_distance = accumulative_distance + light_distance[index];
				accumulative_intensity = accumulative_intensity + light_intensity[index];
				
				//next
				index = index + 1;
			}
		}
		
	if((dis * 1000000) < (0.7*1000000))
	{
	
		//total light distance is two. do only one for now
		float stageone_light_distance = 0.7;
		float stageone_light_intensity = 0.65;
		float stageone_resolution = 1000000;
		float stageone_light_intensity_per_one_resolution = stageone_light_intensity / stageone_resolution;
		float stageone_steps_of_light_distance = stageone_light_distance / stageone_resolution;
		
		float stageone_total_sync_steps = dis / stageone_steps_of_light_distance;
		
		float stageone_final_light_intensity = stageone_light_intensity_per_one_resolution * stageone_total_sync_steps;
		
		
		
		float final_light_intensity = stageone_final_light_intensity;
		
		gl_FragColor = mix(color, nolight, final_light_intensity);
		
	}else if((dis * 1000000) >= (0.7*1000000) && (dis * 1000000) < (1.0*1000000))
	{
		float stageone_light_distance = 0.3;
		float stageone_light_intensity = 1.0;
		float stageone_resolution = 1000000;
		float stageone_light_intensity_per_one_resolution = stageone_light_intensity / stageone_resolution;
		float stageone_steps_of_light_distance = stageone_light_distance / stageone_resolution;
		
		float stageone_total_sync_steps = (dis-0.7) / stageone_steps_of_light_distance;
		
		float stageone_final_light_intensity = stageone_light_intensity_per_one_resolution * stageone_total_sync_steps;
		
		
		
		float final_light_intensity = stageone_final_light_intensity + 0.65;
		
		
		gl_FragColor = mix(color, nolight, final_light_intensity);
		

	}else{
		gl_FragColor = vec4(vec3(0.0), 1.0);
		
	}
}	








