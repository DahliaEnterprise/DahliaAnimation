#ifndef GAME_H
#define GAME_H

#include <QObject>

#include "./state_machine/models/models.h"
#include "./state_machine/game/scene/scenes.h"


class game : public QObject
{
    Q_OBJECT
public:
    game();
		
		void initialize(models * model_information);
		
		void scene_iterate();
		
		void render();
		
		void associate_color_shader(QOpenGLShaderProgram * color_shader_program);
		
		
private:
	models * ptr_to_models;
	
	scenes * scene_information;
	
};

#endif // GAME_H
