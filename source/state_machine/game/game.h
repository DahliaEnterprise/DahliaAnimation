#ifndef GAME_H
#define GAME_H

#include <QObject>

#include "./state_machine/models/models.h"

class game
{
    Q_OBJECT
public:
    game();
		
		void initialize(models * model_information);
		
private:
	models * ptr_to_models;
	
};

#endif // GAME_H
