#ifndef OPENGL_MANAGER_H
#define OPENGL_MANAGER_H
#include "openglwindows.h"
#include <QObject>
class opengl_manager : public QObject
{
    Q_OBJECT
public:
    explicit opengl_manager(QObject *parent = nullptr);
		void initialize();
		
private:
	openglwindows * window;
		
		
signals:

};

#endif // OPENGL_MANAGER_H
