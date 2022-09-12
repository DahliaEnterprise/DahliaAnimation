#include "openglwindows.h"

openglwindows::openglwindows()
{

}

void openglwindows::initializeGL()
{
	
	stoplight_positions_vertex_group = new vertex_group();
	stoplight_positions_vertex_group->setPositions(QUrl("./../DahliaAnimation/source/stoplightray_balls/triangle.xyz"));

	
  initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 1.0f, 0.9f);
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
	
	  //load shadow balls
		/*GLfloat * stoplight_positions = stoplight_positions_vertex_group->getTrianglePositions();
		
		QVector3D stoplight_points[stoplight_positions_vertex_group->getTotalTrianglePositions()];
		unsigned int index = 0;
		unsigned int stoplight_points_index = 0;
		while(index < stoplight_positions_vertex_group->getTotalTrianglePositions())
		{
			stoplight_points[stoplight_points_index] = QVector3D(stoplight_positions[index], stoplight_positions[index+1], stoplight_positions[index+2]);
			
			stoplight_points_index = stoplight_points_index + 1;
			index = index + 3;
		}
		*/
	
	scene_major_one->iterate();
	scene_major_one->render();
	
		//update visual physical frame
		this->update();
	QTimer::singleShot((1000/60), this, SLOT(run_paint()));
	
}
