#ifndef STATE_OF_MODEL_H
#define STATE_OF_MODEL_H

#include <QObject>


#include "vertex_group.h"
#include "./state_machine/tuple_float/tuple_float.h"


class state_of_model : public QObject
{
    Q_OBJECT
public:
    explicit state_of_model(QObject *parent = nullptr);

		void initialize(int array_size_of_tuple);
		
		//set/get render options
		void set_flag_allocate();
		void set_flag_render_model(int do_render_flag);
		int get_flag_render_model();
		void set_flag_vbo();
		int get_flag_vbo();
		
		void load_vertex_positions(QString vertex_positions_filelocation);
		void load_vertex_colors(QString vertex_colors_filelocation);
		vertex_group * get_vertex_group();
		GLfloat * get_combined_tuple(int * array_of_index);
		int get_combined_size(int * array_of_index);
		
		void translate(GLfloat add_x_offset, GLfloat add_y_offset, GLfloat add_z_offset);
		void rotate(GLfloat add_x_rotation, GLfloat add_y_rotation, GLfloat add_z_rotation);
		
		float get_x_offset();
		float get_y_offset();
		float get_z_offset();
		
		float get_x_rotation();
		float get_y_rotation();
		float get_z_rotation();
		
		
	private:
		int flag_render_model;
		int flag_write_vbo;
		
		vertex_group * vertex_and_secondary_unaltered;
		vertex_group * vertex_and_secondary_altered;
		
		tuple_float * tuple_unaltered;
		
		float x_rotation;
		float y_rotation;
		float z_rotation;
		
		float x_offset;
		float y_offset;
		float z_offset;
		
		
signals:

};

#endif // STATE_OF_MODEL_H
