#ifndef SCENE_ONE_H
#define SCENE_ONE_H

#include <QObject>
#include <QFile>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "./state_machine/state_of_model/state_of_model.h"
#include "./tool/model_viewer/model_viewer.h"
#include "./state_machine/scene_tool/load_and_compile_shader/load_and_compile_shader.h"

class scene_one : public QObject
{
    Q_OBJECT
public:
    explicit scene_one(QObject *parent = nullptr);
		
		void iterate();
		
		void associate_color_shader(QOpenGLShaderProgram * set_color_shader_program);
		
		void render();
		
private:
		model_viewer * tool_model_viewer;
		
		load_and_compile_shader * load_shader;
		int prestage;
	
		QOpenGLShaderProgram * color_shader_program;
		QOpenGLShaderProgram * line_shader_program;
		
		QMap<QString, state_of_model *> * list_of_models;
		
		void draw_arrays_using_color_shader(char * model_name, QOpenGLVertexArrayObject * vao, QOpenGLBuffer * vbo, int total_points_of_triangles);
		
		
signals:

};

#endif // SCENE_ONE_H
