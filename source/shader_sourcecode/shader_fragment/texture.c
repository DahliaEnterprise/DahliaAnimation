#version 330
in vec2 texture_position;

uniform sampler2D texture_slot;

float light_intensity_factor(in float light_source_distance)
{
	float result = 0.50;
	float max_distance = 2.0;
	float light_intensity[3];
  	float light_intensity_position[3];
  	
	light_intensity[0] = 0.0; 
	light_intensity[1] = 0.5; 
	light_intensity[2] = 1.0;
	
	light_intensity_position[0] = 0.0; 				light_intensity_position[1] = 0.2; 					light_intensity_position[2] = 1.0;
	
	int light_info_index = 0;
	/*	while(light_info_index < 3)
	{
		if((light_intensity_position[light_info_index] < light_source_distance)
		{
			if(light_intensity_position[light_info_index+1] > light_source_distance)
			{
				//float closest_lowest_position = 0;
				float closest_higher_position = light_intensity_position[light_info_index+1] - light_intensity_position[light_info_index];\n							 float position_difference = closest_higher_position - (light_source_distance - light_intensity_position[light_info_index]);\n							 result = position_difference;						
			}\n					
		}*/
	return result;
}

void main( void )
{
	/*vec4 nolight_color = vec4(0.0, 0.0, 0.0, 1.0);
	vec3 light_position = vec3(0.0, 0.5, 0.0);
	float light_distance = distance(vertex_position, vec4(light_position, 1.0));
	float light_intensity = light_intensity_factor(light_distance);
	vec4 mixed_color = mix(nolight_color, color, light_intensity);
	gl_FragColor = mixed_color;*/
	
	gl_FragColor = texture(texture_slot, texture_position);
}	