#include "controller_three_triangles.h"

controller_three_triangles::controller_three_triangles(QObject *parent)
    : QObject{parent}
{

}


void controller_three_triangles::initialize(QMap<QString, state_of_model *> * set_list_of_models)
{
	ptr_to_list_of_models = set_list_of_models;
	
	set_list_of_models->value("triangle_one")->scale(-0.9, -0.9, -0.9);
	set_list_of_models->value("triangle_one")->set_flag_render_model(1);
	
	set_list_of_models->value("triangle_one")->translate(0.0, 0.5, 0.0);
	
	
	set_list_of_models->value("triangle_two")->scale(-0.9, -0.9, -0.9);
	set_list_of_models->value("triangle_two")->set_flag_render_model(1);
	
	set_list_of_models->value("triangle_two")->translate(0.0, 0.5, 0.0);
	
	
	set_list_of_models->value("triangle_three")->scale(-0.9, -0.9, -0.9);
	set_list_of_models->value("triangle_three")->set_flag_render_model(1);
	
	set_list_of_models->value("triangle_three")->translate(0.0, 0.5, 0.0);
	
	target_angle_of_triangle = new QVector3D(0.0, 0.0, 0.0);
	
	out_length = 0.1;
	expanding = 1;
}

void controller_three_triangles::iterate()
{
	state_of_model * triangle_one = ptr_to_list_of_models->value("triangle_one");
	triangle_one->set_x_offset(out_length * qCos(target_angle_of_triangle->z()));
	triangle_one->set_y_offset(out_length * qSin(target_angle_of_triangle->z()));
	
	target_angle_of_triangle->setZ(target_angle_of_triangle->z()+0.1);
	triangle_one->rotate(0.00, 0.00 , 0.01);
	
	
	state_of_model * triangle_two = ptr_to_list_of_models->value("triangle_two");
	triangle_two->set_x_offset(out_length * qCos(target_angle_of_triangle->z()+0.5));
	triangle_two->set_y_offset(out_length * qSin(target_angle_of_triangle->z()+0.5));
	
	target_angle_of_triangle->setZ(target_angle_of_triangle->z()+0.1);
	
	state_of_model * triangle_three = ptr_to_list_of_models->value("triangle_three");
	triangle_three->set_x_offset(out_length * qCos(target_angle_of_triangle->z()+1));
	triangle_three->set_y_offset(out_length * qSin(target_angle_of_triangle->z()+1));
	
	target_angle_of_triangle->setZ(target_angle_of_triangle->z()+0.1);
	

//float current_scale_x = ptr_to_list_of_models->value("triangle_one")->get_x_scale();
	if(expanding)
	{
		out_length += 0.01;
		triangle_one->scale(0.01, 0.01, 0.01);
		
		if((out_length * 1000000) >= (1.0 * 1000000))
		{
			expanding = 0;
			out_length = 1.0;
		}
	}else{
		out_length -= 0.01;
		triangle_one->scale(-0.01, -0.01, -0.01);
		
		if((out_length * 1000000) <= (0))
		{
			expanding = 1;
			out_length = 0.0;
		}
	}
}