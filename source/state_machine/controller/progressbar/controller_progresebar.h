#ifndef CONTROLLER_PROGRESEBAR_H
#define CONTROLLER_PROGRESEBAR_H

#include <QObject>

class controller_progresebar : public QObject
{
    Q_OBJECT
public:
    explicit controller_progresebar(QObject *parent = nullptr);

		void initialize(QMap<QString, state_of_model *> * set_list_of_models);
		
private:
		QMap<QString, state_of_model *> * ptr_to_list_of_models;
		
signals:

};

#endif // CONTROLLER_PROGRESEBAR_H
