#include "state_of_model.h"

state_of_model::state_of_model(QObject *parent)
    : QObject{parent}
{

}

void state_of_model::initialize()
{
	flag_render_model = 0;
	flag_allocate_vbo = 1;
	
	vertex_and_secondary = new vertex_group();
}

void state_of_model::set_flag_allocate()
{
	flag_allocate_vbo = 1;
}

void state_of_model::set_flag_render_model(int do_render_flag)
{
	flag_render_model = do_render_flag;
}

int state_of_model::get_flag_render_model()
{
	return flag_render_model;
}

void state_of_model::load_vertex_positions(QString vertex_positions_filelocation)
{
	vertex_and_secondary->setPositions(QUrl(vertex_positions_filelocation));
}

void state_of_model::load_vertex_colors(QString vertex_colors_filelocation)
{
	vertex_and_secondary->setColors(QUrl(vertex_colors_filelocation));
}

vertex_group * state_of_model::get_vertex_group()
{
	return vertex_and_secondary;
}