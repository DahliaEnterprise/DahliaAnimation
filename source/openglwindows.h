#ifndef OPENGLWINDOWS_H
#define OPENGLWINDOWS_H

#include "vertex_group.h"
#include "./rotation_scale_translate/rotation/rotate_2d.h"
#include <QOpenGLWindow>
#include <QObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLPaintDevice>
#include <QDebug>
#include <QTimer>
#include <QVector3D>

#include "./state_machine/state_machine.h"

class openglwindows : public QOpenGLWindow, protected QOpenGLFunctions
{
	Q_OBJECT
	
public:
    openglwindows();
		
		void initializeGL();
  	void resizeGL(int width, int height);
  	void paintGL();

private:
	void load_text_file(QString file_location);
	
	state_machine * statemachine;
	
	QTextStream * text_stream;
	
	QMap<QString, state_of_model*> * ptr_to_state_of_models;
	
	vertex_group * stoplight_positions_vertex_group;


	rotate_2d * rotate;

	//Vertex and pair(color or texture coordinates)
		//Square
		QOpenGLBuffer * square_ogl_vbo_quad;
  	QOpenGLVertexArrayObject square_ogl_vao_quad;
  	vertex_group * square_vertex_and_colors;
		int init_square;
		
		//Triangle
		QOpenGLBuffer * triangle_ogl_vbo_quad;
  	QOpenGLVertexArrayObject triangle_ogl_vao_quad;
		vertex_group * triangle_vertex_and_colors_unaltered;
		vertex_group * triangle_vertex_and_colors_altered;

		
	//Shader programs
	QOpenGLShaderProgram * color_shader_program;
	
signals:

public slots:
	void run_paint();

};

#endif // OPENGLWINDOWS_H
