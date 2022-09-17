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
	
		void render();
		
private:
		model_viewer * tool_model_viewer;
		
		load_and_compile_shader * load_shader;
		int prestage;
	
		QOpenGLShaderProgram * color_shader_program;
		QOpenGLShaderProgram * line_shader_program;
		QOpenGLShaderProgram * texture_shader_program;
		
		QMap<QString, state_of_model *> * list_of_models;
		
		void create_model_positions_and_colors(char * model_name, QString positions_file_location, QString colors_file_location);
		
		
		void draw_arrays_using_color_shader(char * model_name, QOpenGLVertexArrayObject * vao, QOpenGLBuffer * vbo, int total_points_of_triangles);
		void draw_arrays_using_texture_shader(char * model_name, QOpenGLVertexArrayObject * vao, QOpenGLBuffer * vbo, int total_points_of_triangles);
		
		//frame rate independent positions
		float start_x;
		float end_x;
		float current_x;
		float start_y;
		float end_y;
		float current_y;
		float start_z;
		float end_z; 
		float current_z;
		
		float ballsize;
		
signals:

};

#endif // SCENE_ONE_H
