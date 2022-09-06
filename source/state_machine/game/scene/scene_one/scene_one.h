#ifndef SCENE_ONE_H
#define SCENE_ONE_H

#include <QObject>

#include "./state_machine/models/models.h"

class scene_one : public QObject
{
    Q_OBJECT
public:
    explicit scene_one(QObject *parent = nullptr);

		void iterate(models * model_information);
		
		
signals:

};

#endif // SCENE_ONE_H
