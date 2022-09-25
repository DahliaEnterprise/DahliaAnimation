#include "opengl_manager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
		opengl_manager * ogl_manager = new opengl_manager();
										ogl_manager->initialize();
		
    return a.exec();
}
