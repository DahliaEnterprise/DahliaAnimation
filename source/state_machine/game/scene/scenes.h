#ifndef SCENES_H
#define SCENES_H

#include <QObject>

#include "./state_machine/models/models.h"
#include "./state_machine/game/scene/scene_one/scene_one.h"

class scenes : public QObject
{
    Q_OBJECT
public:
    explicit scenes(QObject *parent = nullptr);

		void initialize(models * model_information);
		
		void iterate_scene();
		
		void render();
		
		void associate_color_shader(QOpenGLShaderProgram * color_shader_program);
		
		
private:
		models * ptr_to_models;
		
		int current_scene;
		
		scene_one * scene_major_one;
		
signals:

};

#endif // SCENES_H
