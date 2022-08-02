#ifndef OPENGLWINDOWS_H
#define OPENGLWINDOWS_H

#include <QOpenGLWindow>
#include <QObject>
#include <QOpenGLFunctions>

class openglwindows : public QOpenGLWindow, protected QOpenGLFunctions
{
	Q_OBJECT
	
public:
    openglwindows();
		
		void initializeGL();
  	void resizeGL(int width, int height);
  	void paintGL();
  	void teardownGL();
		
		
};

#endif // OPENGLWINDOWS_H
