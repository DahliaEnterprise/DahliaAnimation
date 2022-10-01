#version 330
in vec4 color;
in vec4 vertex_position;
uniform vec3 stoplight_positions[1024];


void main( void )
{
	int max_int = 2147483647 - 1;
	
	//translate frag coord position to opengl coordinates
	//todo: dynamically generate this shader to have hardcoded printed values of screen width(800) and screen height(600).
	vec3 fragcoord_as_openglcoordspace = vec3((gl_FragCoord.x/800)-0.5, (gl_FragCoord.y/600)-0.5, gl_FragCoord.z);
	
	//color for absent of light.
	vec4 nolight = vec4(0.0, 0.0, 0.0, 1.0);
	
	//position of light (white lights reval the object color).
	vec3 light_position = vec3(0.0, 0.0, -0.09);//keep x the highest number while only supporting x as the master plane during stop light ray ball test.
	
	//position of fragment.
	vec3 fragment_position = fragcoord_as_openglcoordspace;
	
	//stop light if ray hits a stoplight ball
	int flag_nolight = 0;
	vec3 stoplight_ball_location = vec3(0.0, 0.0, -0.05);
	float stoplight_ball_size = 0.2;
	vec3 ray_location = light_position;
	float ray_size = 0.01;
	int continue_ray = 1;
	/*while(continue_ray == 1)
	{
		
	}*/
	
	
	//lighting
	if(flag_nolight == 0)
	{
		float stretch_multiplier = 0.7;
		
		float light_distance[2];
		light_distance[0] = 0.7;
		light_distance[1] = 0.3;
		
		int light_distance_int[2];
		light_distance_int[0] = int((light_distance[0] * 1000000));
		light_distance_int[1] = int((light_distance[1] * 1000000));
		
		float light_intensity[2];
		light_intensity[0] = 0.65;
		light_intensity[1] = 1.0;
		
		
		
		//get distance from light
		float distance_between_fragposition_and_lightposition = distance(fragment_position, light_position);
		highp int distance_between_fragposition_and_lightposition_int = int((distance_between_fragposition_and_lightposition * 1000000));
		if(distance_between_fragposition_and_lightposition_int < (light_distance[0] * 1000000))
		{
			float stageone_light_distance = light_distance[0];
			float stageone_light_intensity = light_intensity[0];
			float stageone_resolution = 1000000;
			float stageone_light_intensity_per_one_resolution = stageone_light_intensity / stageone_resolution;
			float stageone_steps_of_light_distance = stageone_light_distance / stageone_resolution;
			
			float stageone_total_sync_steps = distance_between_fragposition_and_lightposition / stageone_steps_of_light_distance;
			
			float stageone_final_light_intensity = stageone_light_intensity_per_one_resolution * stageone_total_sync_steps;
			
			float final_light_intensity = stageone_final_light_intensity * stretch_multiplier;
			
			gl_FragColor = mix(color, nolight, final_light_intensity);
			flag_nolight = 0;
		}else if(distance_between_fragposition_and_lightposition_int > light_distance_int[0] && distance_between_fragposition_and_lightposition_int < (light_distance_int[0] + light_distance_int[1]))
			 {
				float stageone_light_distance = light_distance[1];
				float stageone_light_intensity = light_intensity[1];
				float stageone_resolution = 1000000;
				float stageone_light_intensity_per_one_resolution = stageone_light_intensity / stageone_resolution;
				float stageone_steps_of_light_distance = stageone_light_distance / stageone_resolution;
				
				float stageone_total_sync_steps = (distance_between_fragposition_and_lightposition-0.7) / stageone_steps_of_light_distance;
				
				float stageone_final_light_intensity = stageone_light_intensity_per_one_resolution * stageone_total_sync_steps;
				
				float final_light_intensity = (stageone_final_light_intensity + 0.65) * stretch_multiplier;
				
				gl_FragColor = mix(color, nolight, final_light_intensity);
			
			
		}else
		{
			gl_FragColor = nolight;
		}
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









