#include "state_machine.h"

state_machine::state_machine(QObject *parent)
    : QObject{parent}
{

}

void state_machine::initialize()
{
	model_information = new models();
	model_information->initialize();
	
	game_information = new game();
	game_information->initialize(model_information);
}

models * state_machine::get_model_information()
{
	return model_information;
}

game * state_machine::get_game_information()
{
	return game_information;
}

short int state_machine::show_square()
{
	return 0;
}


