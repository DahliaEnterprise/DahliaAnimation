#include "opengl_manager.h"

opengl_manager::opengl_manager(QObject *parent) : QObject(parent)
{

}

void opengl_manager::initialize()
{
	QSurfaceFormat format;
  format.setRenderableType(QSurfaceFormat::OpenGL);
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setVersion(3,3);
	format.setSamples(4);
	window = new openglwindows();
	window->setFormat(format);
  window->resize(QSize(800, 600));
  window->show();
}