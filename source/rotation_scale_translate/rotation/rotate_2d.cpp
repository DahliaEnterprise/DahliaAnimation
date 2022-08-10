#include "rotate_2d.h"

rotate_2d::rotate_2d(QObject *parent)
{
	
}


GLfloat * rotate_2d::rotate_x(GLfloat * vertex, size_t vertex_memory_size, GLfloat offset_x_rotation)
{
	size_t index = 0;
	while(index < vertex_memory_size)
	{
		GLfloat point_two_z = vertex[index+2];
		GLfloat point_two_y = vertex[index+1];
		
		
		GLfloat * adjacent_opposite_hypotenus = get_two_dimensional_adjacent_opposite_hypotenus( 0, 0, point_two_z, point_two_y);
		GLfloat three_hundred_and_sixty_degrees_as_radians = get_two_dimensional_angle_as_radians(adjacent_opposite_hypotenus[0], adjacent_opposite_hypotenus[2], 0, 0, point_two_z, point_two_y);
		qDebug() << three_hundred_and_sixty_degrees_as_radians;
		
		GLfloat * rotated_point = get_two_dimensional_apply_desired_rotation(three_hundred_and_sixty_degrees_as_radians, offset_x_rotation, adjacent_opposite_hypotenus[2]);
		
		vertex[index+2] = rotated_point[0];
		vertex[index+1] = rotated_point[1];
		
		index = index + 6;
	}
	
	return vertex;
}

GLfloat * rotate_2d::rotate_y(GLfloat * vertex, size_t vertex_memory_size, GLfloat offset_y_rotation)
{
	size_t index = 0;
	while(index < vertex_memory_size)
	{
		GLfloat point_two_z = vertex[index+2];
		GLfloat point_two_x = vertex[index];
		
		
		GLfloat * adjacent_opposite_hypotenus = get_two_dimensional_adjacent_opposite_hypotenus( 0, 0, point_two_z, point_two_x);
		GLfloat three_hundred_and_sixty_degrees_as_radians = get_two_dimensional_angle_as_radians(adjacent_opposite_hypotenus[0], adjacent_opposite_hypotenus[2], 0, 0, point_two_z, point_two_x);
		qDebug() << three_hundred_and_sixty_degrees_as_radians;
		
		GLfloat * rotated_point = get_two_dimensional_apply_desired_rotation(three_hundred_and_sixty_degrees_as_radians, offset_y_rotation, adjacent_opposite_hypotenus[2]);
		
		vertex[index+2] = rotated_point[0];
		vertex[index] = rotated_point[1];
		
		index = index + 6;
	}
	
	return vertex;
}

GLfloat * rotate_2d::rotate_z(GLfloat * vertex, size_t vertex_memory_size, GLfloat offset_z_rotation)
{
	size_t index = 0;
	while(index < vertex_memory_size)
	{
		GLfloat point_two_x = vertex[index];
		GLfloat point_two_y = vertex[index+1];
		
		
		GLfloat * adjacent_opposite_hypotenus = get_two_dimensional_adjacent_opposite_hypotenus( 0, 0, point_two_x, point_two_y);
		GLfloat three_hundred_and_sixty_degrees_as_radians = get_two_dimensional_angle_as_radians(adjacent_opposite_hypotenus[0], adjacent_opposite_hypotenus[2], 0, 0, point_two_x, point_two_y);
		qDebug() << three_hundred_and_sixty_degrees_as_radians;
		
		GLfloat * rotated_point = get_two_dimensional_apply_desired_rotation(three_hundred_and_sixty_degrees_as_radians, offset_z_rotation, adjacent_opposite_hypotenus[2]);
		
		vertex[index] = rotated_point[0];
		vertex[index+1] = rotated_point[1];
		
		index = index + 6;
	}
	
	return vertex;
}

GLfloat * rotate_2d::get_two_dimensional_adjacent_opposite_hypotenus(GLfloat point_one_x, GLfloat point_one_y, GLfloat point_two_x, GLfloat point_two_y)
{
	GLfloat * output = 0; while(output == 0){ output = (GLfloat*)malloc(3 * sizeof(GLfloat)); }
	//adj opposite hypotenus
	
GLfloat adjacent = point_one_x - point_two_x; 
      adjacent = qAbs(adjacent);
      output[0] = adjacent;
  GLfloat adjacent_squared = qPow(adjacent, 2);
    
  ////
  GLfloat opposite = point_one_y - point_two_y;
      opposite = qAbs(opposite);
        output[1] = opposite;
  GLfloat opposite_squared = qPow(opposite, 2);
    
  ///ensure adjacent and opposite are not absolute zero.
  if((adjacent * 1000000) == 0)
  {
    adjacent = 0.000001;
  }
    
  if((opposite * 1000000) == 0)
  {
    opposite = 0.000001;
  }
    
  GLfloat a_squared_plus_b_squared = adjacent_squared + opposite_squared;
  GLfloat hypotenus = qSqrt(a_squared_plus_b_squared);
  output[2] = hypotenus;
	
	return output;
}

GLfloat rotate_2d::get_two_dimensional_angle_as_radians(GLfloat adjacent, GLfloat hypotenus, GLfloat point_one_x, GLfloat point_one_y, GLfloat point_two_x, GLfloat point_two_y)
{
	GLfloat angle_as_radians = -1;
      
  //if any of the points are zero they must be 0.000001 as an integer or magnitude calculations (hypotenus and rotated point combonation results) will be non existent, the result of this function should be uploaded to the gpu and not alter the model data within the source(usually the CPU, or the hardrive when saving the state of the game, make sure to interject and replace with zeros decimals where nessecary if this is being used to store states within long term storage sources or CPU ram dataline transfers), or spin-out-of-control(or strange precision rotations of objects) will happen after a long peroid of time with seemingly no end to debugging.
  if((point_one_x*1000000) == 0){ point_one_x = 0.000001; }
  if((point_one_y*1000000) == 0){ point_one_y = 0.000001; }
  if((point_two_x*1000000) == 0){ point_two_x = 0.000001; }
  if((point_two_y*1000000) == 0){ point_two_y = 0.000001; }
  
  //Determine if starting point(point one x y) is on a quadrant or an exact plane, there is no zero x, zero y during these calculations due to the magnitude determination collapse problem.
  short int quadrant = -1; //0 = bottom-left to top-right(0-90), 1 = bottom-right to top-left(90-180), 2 = top-right to bottom-left(180-270), 3 = top-left to bottom-right(270-360).
  short int exact_plane = -1; //0 = left to exactly right(0), 1 = bottom to exactly top(90), 2 = right to exactly left(180), 3 = top to exactly bottom(270).
  
  
  //a conversion to integers then comparision in integers is garunteed while decimal only comparisons will garuntee error/failure without debugging possibilities had you not known this about transistor computation flaws.
  GLfloat point_one_x_integer = point_one_x*1000000;
  GLfloat point_one_y_integer = point_one_y*1000000;
  GLfloat point_two_x_integer = point_two_x*1000000;
  GLfloat point_two_y_integer = point_two_y*1000000;
	
  //the following conditionals are upon an infinite grid with no orientation until exactly upon determiniation when checked by the second point x and y coordinates. the starting point is finite while the ending point is both finite and infinite in order to discover a floating angle direction of a precision of eight directions(up, right, down, left and their diagonals).
  if(point_one_x_integer > point_two_x_integer)
  {
    if(point_one_y_integer > point_two_y_integer)
    {
      //start is exactly somewhere finite within the top right, second point is some where in a finite but only known as infinite angle within the bottom left.
      quadrant = 2;
    }else if(point_one_y_integer < point_two_y_integer)
    {
      //start is exactly somewhere finite within the bottom right, second point is some where in a finite but only known as infinite angle within the top left.
      quadrant = 1;
    }else if(point_one_y_integer == point_two_y_integer)
    {
      //start is exactly right of second x y coordinates, second point is exactly left of first point.
      exact_plane = 2;
    }
  }else if(point_one_x_integer < point_two_x_integer)
  {
    if(point_one_y_integer > point_two_y_integer)
    {
      //start is exactly top left, second point is bottom right.
      quadrant = 3;
    }else if(point_one_y_integer < point_two_y_integer)
    {
      //start is exactly bottom-left and second point is top-right.
      quadrant = 0;
    }else if(point_one_y_integer == point_two_y_integer)
    {
      //start is exactly left, second point is exactly right.
      exact_plane = 0;
    }
  }else if(point_one_x_integer == point_two_x_integer)
  {
    if(point_one_y_integer > point_two_y_integer)
    {
      //exact start is top and exact second point is bottom.
      exact_plane = 3;
    }else if(point_one_y_integer < point_two_y_integer)
    {
      //exact start is bottom and exact second point is top.
      exact_plane = 1;
    }
  }
  
  
  //angle with a precision of eight directions is determined, now to determine the magnitude of the line.
  GLfloat three_hundred_and_sixty_degrees_as_radians = -1;
  if((adjacent*1000000) == 0)
  {
    adjacent = 0.000001;
  }
 
  //determine angle as radians.
  if(quadrant != -1)
  {
    if(quadrant == 0)
    {
      //zero to ninety, top right.
      three_hundred_and_sixty_degrees_as_radians = qAcos(adjacent / hypotenus);
    }else if(quadrant == 1)
    {
      //nintey to one hundred and eighty, top left.
      three_hundred_and_sixty_degrees_as_radians = 3.141592 - qAcos(adjacent / hypotenus);
    }else if(quadrant == 2)
    {
      //one hundred and eighty to two hundred and seventy, bottom left.
      three_hundred_and_sixty_degrees_as_radians = 3.141592 + qAcos(adjacent / hypotenus);
    }else if(quadrant == 3)
    {
      //two hundred and seventy to three hundred and sixty, bottom right
      three_hundred_and_sixty_degrees_as_radians = 3.141592 + (3.141592 - qAcos(adjacent / hypotenus));
    }
  }else if(exact_plane != -1)
  {
    if(exact_plane == 0)
    {
      //zero degrees
      three_hundred_and_sixty_degrees_as_radians = 0.000000;
    }else if(exact_plane == 1)
    {
      //ninety degrees
      three_hundred_and_sixty_degrees_as_radians = 1.570796;
    }else if(exact_plane == 2)
    {
      //one hundred and eighty degrees
      three_hundred_and_sixty_degrees_as_radians = 3.141592;
    }else if(exact_plane == 3)
    {
      //two hundred and seventy
      three_hundred_and_sixty_degrees_as_radians = 4.712388;
    }
  }
  //define angle as radians that has been calculated.
  angle_as_radians = three_hundred_and_sixty_degrees_as_radians;
  
  //return angle in radians format 
  return angle_as_radians;
}

GLfloat * rotate_2d::get_two_dimensional_apply_desired_rotation(GLfloat current_angle_as_radians, GLfloat offset_angle_as_radians, GLfloat hypotenus)
{
  GLfloat * output = 0; while(output == 0){output = (GLfloat*)malloc(2*sizeof(GLfloat));}
   
  GLfloat rotated_angle = 0.000000;
  rotated_angle += current_angle_as_radians;
  rotated_angle += offset_angle_as_radians;
    
  
  GLfloat rotated_x = hypotenus * qCos(rotated_angle);
  GLfloat rotated_y = hypotenus * qSin(rotated_angle);
  
  
  output[0] = rotated_x;
  output[1] = rotated_y;
  
  return output;
}