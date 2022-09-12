#ifndef LOAD_AND_COMPILE_SHADER_H
#define LOAD_AND_COMPILE_SHADER_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QTextStream>
#include <QFile>

class load_and_compile_shader : public QObject
{
    Q_OBJECT
public:
    explicit load_and_compile_shader(QObject *parent = nullptr);
		void loadVertex(QString file_location);
		void vertex_readAll();
		void addVertexShaderFromSourceCode();
		
		void loadFragment(QString file_location);
		void fragment_readAll();
		void addFragmentShaderFromSourceCode();
		
		QOpenGLShaderProgram * get_shader_program();
		
private:
		QOpenGLShaderProgram * shader_program;
		
		QFile * color_vertex_shader_file;
		QFile * color_fragment_shader_file;
		QTextStream * text_stream;
		std::string vertex_shader_source_code;
		std::string fragment_shader_source_code;
		
signals:

};

#endif // LOAD_AND_COMPILE_SHADER_H
