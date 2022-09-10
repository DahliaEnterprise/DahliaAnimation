#ifndef SCENE_ONE_H
#define SCENE_ONE_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

#include "./state_machine/models/models.h"

class scene_one : public QObject
{
    Q_OBJECT
public:
    explicit scene_one(QObject *parent = nullptr);

		void iterate(models * model_information);
		
		void associate_color_shader(QOpenGLShaderProgram * set_color_shader_program);
		
		void render(models * model_information);
		
private:
		QOpenGLShaderProgram * color_shader_program;
		
signals:

};

#endif // SCENE_ONE_H
