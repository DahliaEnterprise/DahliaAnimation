#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 incolor;
out vec4 color;
out vec4 vertex_position;

uniform vec3 offset_position_rotation[3];

mat3 matrix_rotate_z(float angle)
{
  float s = sin(angle);
  float c = cos(angle);

  return mat3(
    c, s, 0.0,
    -s, c, 0.0,
    0.0, 0.0, 1.0
  );
}

mat3 matrix_rotate_y(float angle) 
{
  float s = sin(angle);
  float c = cos(angle);

  return mat3(
    c, 0.0, -s,
    0.0, 1.0, 0.0,
    s, 0.0, c
  );
}

mat3 matrix_rotate_x(float angle)
{
  float s = sin(angle);
  float c = cos(angle);

  return mat3(
    1.0, 0.0, 0.0,
    0.0, c, s,
    0.0, -s, c
  );
}

void main( void )
{
	vec3 new_position = position;
	
	
	//scale, rotate, translate
	//apply scale
	new_position.x = new_position.x * offset_position_rotation[2].x;
	new_position.y = new_position.y * offset_position_rotation[2].y;
	new_position.z = new_position.z * offset_position_rotation[2].z;
	
	//apply rotation
	new_position = new_position * matrix_rotate_z(offset_position_rotation[1].z);
	new_position = new_position * matrix_rotate_y(offset_position_rotation[1].y);
	new_position = new_position * matrix_rotate_x(offset_position_rotation[1].x);
	
	//translate position
	new_position.x += offset_position_rotation[0].x;
	new_position.y += offset_position_rotation[0].y;
	new_position.z += offset_position_rotation[0].z;
	
	
	
	//apply depth perspective(this might be replqced with glpersoective, not clear)
	//new_position.x = new_position.x / new_position.z;
	//new_position.y = new_position.y / new_position.z;
	
	gl_Position = vec4(new_position, 1.0);
	
	color = vec4(incolor, 1.0);
	
}
