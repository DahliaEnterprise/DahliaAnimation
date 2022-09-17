#ifndef META_MODEL_VIEWER_H
#define META_MODEL_VIEWER_H

#include <QObject>

class meta_model_viewer : public QObject
{
    Q_OBJECT
public:
    explicit meta_model_viewer(QObject *parent = nullptr);

signals:

};

#endif // META_MODEL_VIEWER_H
