#include "game.h"

game::game()
{

}

void game::initialize(models * model_information)
{
	ptr_to_models = model_information;
	
	scene_information = new scenes();
	scene_information->initialize(model_information);
	
}


void game::scene_iterate()
{
	scene_information->iterate_scene();
}

void game::render()
{
	scene_information->render();
}

void game::associate_color_shader(QOpenGLShaderProgram * color_shader_program)
{
	scene_information->associate_color_shader(color_shader_program);
}