#ifndef LOAD_AND_COMPILE_SHADER_H
#define LOAD_AND_COMPILE_SHADER_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QTextStream>
#include <QFile>
#include <QString>

class load_and_compile_shader : public QObject
{
    Q_OBJECT
public:
    explicit load_and_compile_shader(QObject *parent = nullptr);
		void loadVertex(QString file_location);
		void vertex_readAll();
		void vertex_read(qint64 max_to_read);
		void addVertexShaderFromSourceCode();
		
		void loadFragment(QString file_location);
		void fragment_readAll();
		void fragment_read(qint64 max_to_read);
		void addFragmentShaderFromSourceCode();
		
		void clear();
		
		QOpenGLShaderProgram * get_shader_program();
		

private:
		QOpenGLShaderProgram * shader_program;
		
		QFile * vertex_shader_file;
		QFile * fragment_shader_file;
		QTextStream * text_stream;
		QString vertex_shader_source_code;
		QString fragment_shader_source_code;
		
signals:

};

#endif // LOAD_AND_COMPILE_SHADER_H
