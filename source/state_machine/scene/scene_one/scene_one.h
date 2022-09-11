#ifndef SCENE_ONE_H
#define SCENE_ONE_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "./state_machine/state_of_model/state_of_model.h"

class scene_one : public QObject
{
    Q_OBJECT
public:
    explicit scene_one(QObject *parent = nullptr);
		
		void iterate();
		
		void associate_color_shader(QOpenGLShaderProgram * set_color_shader_program);
		
		void render();
		
private:
		int prestage;
	
		QOpenGLShaderProgram * color_shader_program;
		
		QMap<QString, state_of_model *> * list_of_models;
signals:

};

#endif // SCENE_ONE_H
