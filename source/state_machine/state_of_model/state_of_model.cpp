#include "state_of_model.h"

state_of_model::state_of_model(QObject *parent)
    : QObject{parent}
{

}

void state_of_model::initialize(int array_size_of_tuple)
{
	flag_render_model = 0;
	flag_write_vbo = 1;
	
	vertex_and_secondary_unaltered = new vertex_group();
	vertex_and_secondary_altered = new vertex_group();
	
	tuple_unaltered = new tuple_float();
	tuple_unaltered->initialize(array_size_of_tuple);
	
	
	x_rotation = 0.0;
	y_rotation = 0.0;
	z_rotation = 0.0;
}

void state_of_model::set_flag_vbo()
{
	flag_write_vbo = 1;
}

int state_of_model::get_flag_vbo()
{
	return flag_write_vbo;
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
	vertex_and_secondary_unaltered->setPositions(QUrl(vertex_positions_filelocation));
	
	tuple_unaltered->setFloatArray_by_file(0, vertex_positions_filelocation);
}

void state_of_model::load_vertex_colors(QString vertex_colors_filelocation)
{
	vertex_and_secondary_unaltered->setColors(QUrl(vertex_colors_filelocation));
	
	tuple_unaltered->setFloatArray_by_file(1, vertex_colors_filelocation);
	
}

vertex_group * state_of_model::get_vertex_group()
{
	return vertex_and_secondary_unaltered;
}

GLfloat * state_of_model::get_combined_tuple(int * array_of_index)
{
	return tuple_unaltered->get_combined_tuple(array_of_index);
	
}

int state_of_model::get_combined_size(int * array_of_index)
{
	return tuple_unaltered->get_combined_size(array_of_index);
	
}

/*void state_of_model::set_positions_and_colors(GLfloat * positions_and_colors)
{
	vertex_and_secondary_altered->setCombinedXyzColors(positions_and_colors, vertex_and_secondary_altered->combined_total_xyz_colors());
}*/

/*void state_of_model::rotate_z(float rotation_radians)
{
	z_rotation = rotation_radians;
}*/

float state_of_model::get_z_rotation()
{
	return z_rotation;
}