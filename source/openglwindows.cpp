#include "openglwindows.h"

openglwindows::openglwindows()
{

}

void openglwindows::initializeGL()
{
	
  initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	qDebug() << "initializing";
	
	
	scene_major_one = new scene_one();
	
	//start painting
	qDebug() << "run";
	QTimer::singleShot(200, this, SLOT(run_paint()));
	
}
 
void openglwindows::resizeGL(int width, int height)
{
  (void)width;
  (void)height;
}
 
void openglwindows::paintGL()
{
	
}
 
void openglwindows::run_paint()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	
	scene_major_one->iterate();
	scene_major_one->render();
	
		//update visual physical frame
		this->update();
		
	QTimer::singleShot((1000/60), this, SLOT(run_paint()));
	
}
