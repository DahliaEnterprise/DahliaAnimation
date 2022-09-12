#include "load_and_compile_shader.h"

load_and_compile_shader::load_and_compile_shader(QObject *parent)
    : QObject{parent}
{

}

void load_and_compile_shader::loadVertex(QString file_location)
{
	color_vertex_shader_file = new QFile(file_location);
	if(color_vertex_shader_file->exists() == false)
	{
		qDebug() << " must be a valid file.";
	}else{
		bool open_success = color_vertex_shader_file->open(QIODevice::ReadOnly | QIODevice::Text);
		if(open_success == false)
		{
			qDebug() << " file unable to open.";
		}else{
			
		}
	}
	text_stream = new QTextStream();
	text_stream->setDevice(color_vertex_shader_file);
  
}
void load_and_compile_shader::vertex_readAll()
{
	QString text_qstring = text_stream->readAll();
	vertex_shader_source_code = text_qstring.toUtf8().toStdString();
}

void load_and_compile_shader::addVertexShaderFromSourceCode()
{
	shader_program = new QOpenGLShaderProgram();
	bool success = shader_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertex_shader_source_code.c_str());
	if(!success) {
		qDebug() << "vertex";
	}
}

void load_and_compile_shader::loadFragment(QString file_location)
{
	color_fragment_shader_file = new QFile(file_location);
	if(color_fragment_shader_file->exists() == false)
	{
		qDebug() << " must be a valid file.";
	}else{
		bool open_success = color_fragment_shader_file->open(QIODevice::ReadOnly);
		if(open_success == false)
		{
			qDebug() << " file unable to open.";
		}else{
			
		}
	}
	text_stream->setDevice(color_fragment_shader_file);
  
}
void load_and_compile_shader::fragment_readAll()
{
	QString text_qstring = text_stream->readAll();
	fragment_shader_source_code = text_qstring.toUtf8().toStdString();
}

void load_and_compile_shader::addFragmentShaderFromSourceCode()
{
	bool success = shader_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragment_shader_source_code.c_str());
	if(!success) {
		qDebug() << "vertex";
	}
}

QOpenGLShaderProgram * load_and_compile_shader::get_shader_program()
{
	return shader_program;
}
