#ifndef OPENGLWINDOWS_H
#define OPENGLWINDOWS_H

#include "vertex_group.h"
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
#include "state_machine/scene/scene_one/scene_one.h"


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
	
	
	QTextStream * text_stream;
	
	vertex_group * stoplight_positions_vertex_group;

	scene_one * scene_major_one;
	
	//Shader programs
	QOpenGLShaderProgram * color_shader_program;
	
signals:

public slots:
	void run_paint();

};

#endif // OPENGLWINDOWS_H
