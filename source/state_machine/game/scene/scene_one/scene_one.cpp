#include "scene_one.h"

scene_one::scene_one(QObject *parent)
    : QObject{parent}
{

}
int flash_square = 0;
void scene_one::iterate(models * model_information)
{
	if(flash_square == 0)
	{
		flash_square = 1;
		
	}else{
		flash_square = 0;
		
	}

	model_information->get_state_of_models()->value("square")->set_flag_render_model(flash_square);
	model_information->get_state_of_models()->value("square")->set_flag_vbo();
	
	model_information->get_state_of_models()->value("triangle")->set_flag_render_model(1);
	model_information->get_state_of_models()->value("triangle")->set_flag_vbo();
	
	model_information->get_state_of_models()->value("triangle")->rotate(0.0, 0.0, 0.1);
	
	
	//offset
	//model_information->get_state_of_models()->value("square")->translate(0.001, 0.0, 0.0);
	//model_information->get_state_of_models()->value("square")->rotate(0.0, 0.0, 0.01);
	
	

}