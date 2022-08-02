#include "openglwindows.h"

openglwindows::openglwindows()
{

}

void openglwindows::initializeGL()
{
  // Initialize OpenGL Backend
  initializeOpenGLFunctions();
 
  // Set global information
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
 
void openglwindows::resizeGL(int width, int height)
{
  // Currently we are not handling width/height changes
  (void)width;
  (void)height;
}
 
void openglwindows::paintGL()
{
  // Clear
  glClear(GL_COLOR_BUFFER_BIT);
}
 
void openglwindows::teardownGL()
{
  // Currently we have no data to teardown
}