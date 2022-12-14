#include "state_of_model.h"

state_of_model::state_of_model(QObject *parent)
    : QObject{parent}
{

}

void state_of_model::initialize(int array_size_of_tuple)
{
	flag_render_model = 0;
	
	tuple_unaltered = new tuple_float();
	tuple_unaltered->initialize(array_size_of_tuple);
	
	
	x_rotation = 0.0;
	y_rotation = 0.0;
	z_rotation = 0.0;
	
	x_offset = 0.0;
	y_offset = 0.0;
	z_offset = 0.0;
	
	x_scale = 1.0;
	y_scale = 1.0;
	z_scale = 1.0;
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
	tuple_unaltered->setFloatArray_by_file(0, vertex_positions_filelocation);
}

void state_of_model::load_vertex_colors(QString vertex_colors_filelocation)
{
	tuple_unaltered->setFloatArray_by_file(1, vertex_colors_filelocation);
	
}

void state_of_model::load_vertex_texture_positions(QString vertex_texture_positions_filelocation)
{
	tuple_unaltered->setFloatArray_by_file(1, vertex_texture_positions_filelocation);
	
}


GLfloat * state_of_model::get_combined_tuple(int * array_of_index, int * array_of_vector_size)
{
	return tuple_unaltered->get_combined_tuple(array_of_index, array_of_vector_size);
	
}

int state_of_model::get_combined_size(int * array_of_index)
{
	return tuple_unaltered->get_combined_size(array_of_index);
	
}

void state_of_model::translate(GLfloat add_x_offset, GLfloat add_y_offset, GLfloat add_z_offset)
{
	x_offset += add_x_offset;
	y_offset += add_y_offset;
	z_offset += add_z_offset;
	
}

void state_of_model::rotate(GLfloat add_x_rotation, GLfloat add_y_rotation, GLfloat add_z_rotation)
{
	
	x_rotation += add_x_rotation;
	y_rotation += add_y_rotation;
	z_rotation += add_z_rotation;
	
}

void state_of_model::scale(GLfloat add_x_scale, GLfloat add_y_scale, GLfloat add_z_scale)
{
	x_scale += add_x_scale;
	y_scale += add_y_scale;
	z_scale += add_z_scale;
}

void state_of_model::set_x_offset(float new_offset)
{
	x_offset = new_offset;
	
}

float state_of_model::get_x_offset()
{
	return x_offset;
}

void state_of_model::set_y_offset(float new_offset)
{
	y_offset = new_offset;
	
}

float state_of_model::get_y_offset()
{
	return y_offset;
}

void state_of_model::set_z_offset(float new_offset)
{
	z_offset = new_offset;
	
}

float state_of_model::get_z_offset()
{
	return z_offset;
}

float state_of_model::get_x_rotation()
{
	return x_rotation;
}

float state_of_model::get_y_rotation()
{
	return y_rotation;
}

float state_of_model::get_z_rotation()
{
	return z_rotation;
}

float state_of_model::get_x_scale()
{
	return x_scale;
}

void state_of_model::set_x_scale(float set_x_scale)
{
	x_scale = set_x_scale;
}

float state_of_model::get_y_scale()
{
	return y_scale;
}

float state_of_model::get_z_scale()
{
	return z_scale;
}

void state_of_model::associate_vao(QOpenGLVertexArrayObject * set_vao)
{
	vao = set_vao;
}

void state_of_model::associate_vbo(QOpenGLBuffer * set_vbo)
{
	vbo = set_vbo;
}

QOpenGLVertexArrayObject * state_of_model::get_vao()
{
	return vao;
}

QOpenGLBuffer * state_of_model::get_vbo()
{
	return vbo;
}

void state_of_model::set_texture_image(QImage image)
{
	texture = new QOpenGLTexture(image);
	
}

QOpenGLTexture * state_of_model::get_texture()
{
	return texture;
}

long int state_of_model::get_total_points()
{
	int * array_of_index = 0; while(array_of_index == 0){ array_of_index = (int*)malloc(2*sizeof(GLfloat));} array_of_index[0] = 0; array_of_index[1] = 1;
	long int total_points = tuple_unaltered->get_combined_size(array_of_index);
	free(array_of_index);
	
	
	return total_points;
}
