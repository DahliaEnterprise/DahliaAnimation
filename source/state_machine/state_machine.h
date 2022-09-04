#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <QObject>

#include "./state_machine/models/models.h"
#include "./state_machine/game/game.h"

class state_machine : public QObject
{
    Q_OBJECT
public:
    explicit state_machine(QObject *parent = nullptr);
		
		void initialize();
		
		models * get_model_information();
		
		game * get_game_information();
		
		short int show_square();

private:
		models * model_information;
	
		game * game_information;
	
signals:

};

#endif // STATE_MACHINE_H
