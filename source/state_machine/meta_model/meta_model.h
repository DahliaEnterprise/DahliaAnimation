#ifndef META_MODEL_H
#define META_MODEL_H

#include <QObject>

class meta_model : public QObject
{
    Q_OBJECT
public:
    explicit meta_model(QObject *parent = nullptr);

signals:

};

#endif // META_MODEL_H
