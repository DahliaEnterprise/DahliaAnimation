uniform sampler2D texture;
varying mediump vec4 texc;
void main(void)
{
	
	vec4 color = texture2D(texture, texc.st);
	
	//translate frag coord position to opengl coordinates
	vec3 fragcoord_as_openglcoordspace = vec3(0.0);
	float coordinate_system_conversion_x = -0.5;
	float coordinate_system_conversion_y = -0.5;
	float window_resolution_width = 800.0;
	float window_resolution_height = 600.0;
	fragcoord_as_openglcoordspace.x = (gl_FragCoord.x / window_resolution_width) - coordinate_system_conversion_x;
	fragcoord_as_openglcoordspace.y = (gl_FragCoord.y / window_resolution_height) - coordinate_system_conversion_y;
	fragcoord_as_openglcoordspace.z = gl_FragCoord.z;
	
	//color for absent of light.
	vec4 nolight = vec4(0.0, 0.0, 0.0, 1.0);

	//position of light (white lights reval the object color).
	vec3 light_position = vec3(0.0, 0.0, -0.01);//keep x the highest number while only supporting x as the master plane during stop light ray ball test.
	
	//position of fragment.
	vec3 fragment_position = fragcoord_as_openglcoordspace;
	
	
	float light_to_frag_distance = distance(light_position, fragment_position);
	gl_FragColor = vec4(vec3(light_to_frag_distance, 0.0, 0.0),1.0);
	//gl_FragColor = mix(color, nolight ,0.5);
	/*
	//stop light if ray hits a stoplight ball
	int flag_nolight = 0;
	vec3 stoplight_ball_location = vec3(0.0, 0.0, -0.05);
	float stoplight_ball_size = 0.2;
	vec3 ray_location = light_position;
	float ray_size = 0.01;
	int continue_ray = 1;
	/*while(continue_ray == 1)
	{
		
	}*
	
	
	//lighting
	if(flag_nolight == 0)
	{
		
		float stretch_multiplier = 0.7;
		
		float light_distance[2];
		light_distance[0] = 0.7;
		light_distance[1] = 0.3;
		
		float light_intensity[2];
		light_intensity[0] = 0.65;
		light_intensity[1] = 1.0;
		
		
		
		//get distance from light
		float distance_between_fragposition_and_lightposition = distance(fragment_position, light_position);
		if((distance_between_fragposition_and_lightposition * 1000000.0) < (light_distance[0] * 1000000.0))
		{
			
			float stageone_light_distance = light_distance[0];
			float stageone_light_intensity = light_intensity[0];
			float stageone_resolution = 1000000.0;
			float stageone_light_intensity_per_one_resolution = stageone_light_intensity / stageone_resolution;
			float stageone_steps_of_light_distance = stageone_light_distance / stageone_resolution;
			
			float stageone_total_sync_steps = distance_between_fragposition_and_lightposition / stageone_steps_of_light_distance;
			
			float stageone_final_light_intensity = stageone_light_intensity_per_one_resolution * stageone_total_sync_steps;
			
			float final_light_intensity = stageone_final_light_intensity * stretch_multiplier;
			
			gl_FragColor = mix(color, nolight, final_light_intensity);
			flag_nolight = 0;
			
		}
		
		if((distance_between_fragposition_and_lightposition * 1000000.0) > (light_distance[0] * 1000000.0))
		{
			float light_distance_a = (light_distance[0] * 1000000.0);
			float light_distance_b = (light_distance[1] * 1000000.0);
			float light_distance_ab = light_distance_a + light_distance_b;
			
			if((distance_between_fragposition_and_lightposition * 1000000.0) < light_distance_ab)
			{
			
				float stageone_light_distance = light_distance[1];
				float stageone_light_intensity = light_intensity[1];
				float stageone_resolution = 1000000.0;
				float stageone_light_intensity_per_one_resolution = stageone_light_intensity / stageone_resolution;
				float stageone_steps_of_light_distance = stageone_light_distance / stageone_resolution;
				
				float stageone_total_sync_steps = (distance_between_fragposition_and_lightposition-0.7) / stageone_steps_of_light_distance;
				
				float stageone_final_light_intensity = stageone_light_intensity_per_one_resolution * stageone_total_sync_steps;
				
				float final_light_intensity = (stageone_final_light_intensity + 0.65) * stretch_multiplier;
				
				gl_FragColor = mix(color, nolight, final_light_intensity);
			
			
			}
		}
	}
	*/
	gl_FragColor = texture2D(texture, texc.st);
}