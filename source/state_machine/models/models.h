#ifndef MODELS_H
#define MODELS_H

#include <QObject>
#include <QMap>

#include "./state_machine/state_of_model/state_of_model.h"

class models : public QObject
{
    Q_OBJECT
public:
	explicit models(QObject *parent = nullptr);

	void initialize();
	QMap<QString, state_of_model * > * get_state_of_models();
	
private:
	QMap<QString, state_of_model * > * list_of_models;
		
signals:

};

#endif // MODELS_H
