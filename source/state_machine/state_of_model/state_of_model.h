#ifndef STATE_OF_MODEL_H
#define STATE_OF_MODEL_H

#include <QObject>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

#include "vertex_group.h"
#include "./state_machine/tuple_float/tuple_float.h"


class state_of_model : public QObject
{
    Q_OBJECT
public:
    explicit state_of_model(QObject *parent = nullptr);

		void initialize(int array_size_of_tuple);
		
		//set/get render options
		void set_flag_render_model(int do_render_flag);
		int get_flag_render_model();
		
		void load_vertex_positions(QString vertex_positions_filelocation);
		void load_vertex_colors(QString vertex_colors_filelocation);
		void load_vertex_texture_positions(QString vertex_texture_positions_filelocation);
		
		vertex_group * get_vertex_group();
		GLfloat * get_combined_tuple(int * array_of_index, int * array_of_vector_size);
		int get_combined_size(int * array_of_index);
		
		void translate(GLfloat add_x_offset, GLfloat add_y_offset, GLfloat add_z_offset);
		void rotate(GLfloat add_x_rotation, GLfloat add_y_rotation, GLfloat add_z_rotation);
		void scale(GLfloat add_x_scale, GLfloat add_y_scale, GLfloat add_z_scale);
		
		float get_x_offset();
		float get_y_offset();
		float get_z_offset();
		
		float get_x_rotation();
		float get_y_rotation();
		float get_z_rotation();
		
		float get_x_scale();
		float get_y_scale();
		float get_z_scale();
		
		void associate_vao(QOpenGLVertexArrayObject * set_vao);
		void associate_vbo(QOpenGLBuffer * set_vbo);
		
		QOpenGLVertexArrayObject * get_vao();
		QOpenGLBuffer * get_vbo();
		
		void set_texture_image(QImage image);
		QOpenGLTexture * get_texture();
		
	private:
		int flag_render_model;
		
		tuple_float * tuple_unaltered;
		
		float x_rotation;
		float y_rotation;
		float z_rotation;
		
		float x_offset;
		float y_offset;
		float z_offset;
		
		float x_scale; 
		float y_scale;
		float z_scale;
		
		QOpenGLVertexArrayObject * vao;
		QOpenGLBuffer * vbo;
		
		QOpenGLTexture * texture;
		
signals:

};

#endif // STATE_OF_MODEL_H
