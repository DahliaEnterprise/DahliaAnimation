#include "controller_three_triangles.h"

controller_three_triangles::controller_three_triangles(QObject *parent)
    : QObject{parent}
{

}


void controller_three_triangles::initialize(QMap<QString, state_of_model *> * set_list_of_models)
{
	ptr_to_list_of_models = set_list_of_models;
	
	set_list_of_models->value("triangle")->scale(-0.9, -0.9, -0.9);
	set_list_of_models->value("triangle")->set_flag_render_model(1);
	/*set_list_of_models->value("triangle")->translate(-0.5, -0.5, 0.0);
		*/
	
	expanding = 1;
}

void controller_three_triangles::iterate()
{
	float current_scale_x = ptr_to_list_of_models->value("triangle")->get_x_scale();
	if((current_scale_x * 1000000) <= (0.0 * 1000000))
	{
		expanding = 1;
	}else if((current_scale_x * 1000000) >= (1.0 * 1000000))
	{
		expanding = 0;
	}
	
	if(expanding == 1)
	{
		ptr_to_list_of_models->value("triangle")->scale(0.1, 0.1, 0.1);
		
	}else{
		ptr_to_list_of_models->value("triangle")->scale(-0.1, -0.1, -0.1);
	}
}