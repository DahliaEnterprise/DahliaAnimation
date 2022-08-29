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
		float dis = distance(current_test_position, light_position);
		
		if((dis * 1000000) < (0.7*1000000))
		{
		
			//total light distance is two. do only one for now
			float stageone_light_distance = 0.6;
			float stageone_light_intensity = 0.55;
			float stageone_resolution = 1000000;
			float stageone_light_intensity_per_one_resolution = stageone_light_intensity / stageone_resolution;
			float stageone_steps_of_light_distance = stageone_light_distance / stageone_resolution;
			
			float stageone_total_sync_steps = dis / stageone_steps_of_light_distance;
			
			float stageone_final_light_intensity = stageone_light_intensity_per_one_resolution * stageone_total_sync_steps;
			
			
			
			float final_light_intensity = stageone_final_light_intensity;
			
			gl_FragColor = mix(color, nolight, final_light_intensity);
			
		}else if((dis * 1000000) >= (0.7*1000000) && (dis * 1000000) < (1.0*1000000))
		{
			float stageone_light_distance = 1.0;
			float stageone_light_intensity = 1.0;
			float stageone_resolution = 1000000;
			float stageone_light_intensity_per_one_resolution = stageone_light_intensity / stageone_resolution;
			float stageone_steps_of_light_distance = stageone_light_distance / stageone_resolution;
			
			float stageone_total_sync_steps = (dis-0.7) / stageone_steps_of_light_distance;
			
			float stageone_final_light_intensity = stageone_light_intensity_per_one_resolution * stageone_total_sync_steps;
			
			
			
			float final_light_intensity = stageone_final_light_intensity + 0.65;
			
			
			//gl_FragColor = mix(color, nolight, final_light_intensity);
			
			gl_FragColor = vec4(stoplight_positions[1], 1.0);
	
		}else{
			gl_FragColor = vec4(vec3(0.0), 1.0);
			
		}
		
	/*if((dis * 1000000) < (0.7*1000000))
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
		
	}*/
}	








