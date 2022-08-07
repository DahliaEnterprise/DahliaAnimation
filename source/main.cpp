#include "opengl_manager.h"
#include <QApplication>

static const char *vertexShaderSource =
    "attribute highp vec4 posAttr;\n"
    "attribute lowp vec4 colAttr;\n"
    "varying lowp vec4 col;\n"
    "uniform highp mat4 matrix;\n"
    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = matrix * posAttr;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying lowp vec4 col;\n"
    "void main() {\n"
    "   gl_FragColor = col;\n"
    "}\n";


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
		opengl_manager * ogl_manager = new opengl_manager();
        ogl_manager->initialize();
		
    return a.exec();
}
