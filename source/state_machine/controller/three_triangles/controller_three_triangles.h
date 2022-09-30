#ifndef CONTROLLER_THREE_TRIANGLES_H
#define CONTROLLER_THREE_TRIANGLES_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QtMath>
#include <QVector3D>

#include "./state_machine/state_of_model/state_of_model.h"

class controller_three_triangles : public QObject
{
    Q_OBJECT
public:
    explicit controller_three_triangles(QObject *parent = nullptr);

		void initialize(QMap<QString, state_of_model *> * set_list_of_models);
		
		void iterate();
		
private:
		QMap<QString, state_of_model *> * ptr_to_list_of_models;
		
		QVector3D * target_angle_of_triangle;
		float out_length;
		int expanding;
		
signals:

};

#endif // CONTROLLER_THREE_TRIANGLES_H
