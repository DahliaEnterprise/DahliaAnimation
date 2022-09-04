#include "models.h"

models::models(QObject *parent)
    : QObject{parent}
{

}

void models::initialize()
{
	list_of_models = new QMap<QString, state_of_model*>();
}

QMap<QString, state_of_model*>* models::get_state_of_models()
{
	return list_of_models;
}

