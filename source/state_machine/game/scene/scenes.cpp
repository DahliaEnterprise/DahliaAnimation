#include "scenes.h"

scenes::scenes(QObject *parent)
    : QObject{parent}
{

}

void scenes::initialize(models * model_information)
{
	ptr_to_models = model_information;
	current_scene = 1;
	scene_major_one = new scene_one();
	
}

void scenes::iterate_scene()
{
	scene_major_one->iterate(ptr_to_models);
}

void scenes::render()
{
	scene_major_one->render(ptr_to_models);
}

void scenes::associate_color_shader(QOpenGLShaderProgram * color_shader_program)
{
	scene_major_one->associate_color_shader(color_shader_program);
	
}