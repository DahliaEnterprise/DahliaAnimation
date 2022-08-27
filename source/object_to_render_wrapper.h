#ifndef OBJECT_TO_RENDER_WRAPPER_H
#define OBJECT_TO_RENDER_WRAPPER_H

#include <QObject>

class object_to_render_wrapper : public QObject
{
    Q_OBJECT
public:
    explicit object_to_render_wrapper(QObject *parent = nullptr);

signals:

};

#endif // OBJECT_TO_RENDER_WRAPPER_H
