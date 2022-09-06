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

void models::add_model(QString model_id, state_of_model * model_state_information)
{
	list_of_models->insert(model_id, model_state_information);
}