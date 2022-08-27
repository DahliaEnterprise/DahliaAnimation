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

class openglwindows : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT
	
public:
    openglwindows();
		
		void initializeGL();
  	void resizeGL(int width, int height);
  	void paintGL();

private:
	QOpenGLBuffer * triangle_ogl_vbo_quad;
  QOpenGLVertexArrayObject triangle_ogl_vao_quad;
  
	QOpenGLBuffer * triangle_two_ogl_vbo_quad;
  QOpenGLVertexArrayObject triangle_two_ogl_vao_quad;
  
	
	QOpenGLBuffer * square_ogl_vbo_quad;
  QOpenGLVertexArrayObject square_ogl_vao_quad;
  
	QOpenGLShaderProgram * color_shader_program;
	
	
signals:

public slots:
	void run_paint();

};

#endif // OPENGLWINDOWS_H
