#ifndef STATE_OF_MODEL_H
#define STATE_OF_MODEL_H

#include <QObject>

class state_of_model : public QObject
{
    Q_OBJECT
public:
    explicit state_of_model(QObject *parent = nullptr);

signals:

};

#endif // STATE_OF_MODEL_H
