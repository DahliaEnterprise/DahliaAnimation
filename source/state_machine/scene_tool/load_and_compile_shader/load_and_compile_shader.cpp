#include "load_and_compile_shader.h"

load_and_compile_shader::load_and_compile_shader(QObject *parent)
    : QObject{parent}
{

}

void load_and_compile_shader::loadVertex(QString file_location)
{
	vertex_shader_file = new QFile(file_location);
	if(vertex_shader_file->exists() == false)
	{
		qDebug() << " must be a valid file.";
	}else{
		bool open_success = vertex_shader_file->open(QIODevice::ReadOnly | QIODevice::Text);
		if(open_success == false)
		{
			qDebug() << " file unable to open.";
		}else{
			
		}
	}
	text_stream = new QTextStream();
	text_stream->setDevice(vertex_shader_file);
  
}
void load_and_compile_shader::vertex_readAll()
{
	QString text_qstring = text_stream->readAll();
	//vertex_shader_source_code = text_qstring.toUtf8().toStdString();
	vertex_shader_source_code.append(text_qstring);
	
}

long long int load_and_compile_shader::vertex_read(qint64 max_to_read)
{
	QString text_qstring = text_stream->read(max_to_read);
	//vertex_shader_source_code = text_qstring.toUtf8().toStdString();
	vertex_shader_source_code.append(text_qstring);
	
	return text_qstring.size();
}

void load_and_compile_shader::addVertexShaderFromSourceCode()
{
	shader_program = new QOpenGLShaderProgram();
	bool success = shader_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertex_shader_source_code);
	if(!success) {
		qDebug() << "vertex";
	}
}

void load_and_compile_shader::loadFragment(QString file_location)
{
	fragment_shader_file = new QFile(file_location);
	if(fragment_shader_file->exists() == false)
	{
		qDebug() << " must be a valid file.";
	}else{
		bool open_success = fragment_shader_file->open(QIODevice::ReadOnly);
		if(open_success == false)
		{
			qDebug() << " file unable to open.";
		}else{
			
		}
	}
	text_stream->setDevice(fragment_shader_file);
  
}
void load_and_compile_shader::fragment_readAll()
{
	QString text_qstring = text_stream->readAll();
	//fragment_shader_source_code = text_qstring.toUtf8().toStdString();
	fragment_shader_source_code.append(text_qstring);
}

void load_and_compile_shader::fragment_read(qint64 max_to_read)
{
	QString text_qstring = text_stream->read(max_to_read);
	//vertex_shader_source_code = text_qstring.toUtf8().toStdString();
	fragment_shader_source_code.append(text_qstring);
	
}

void load_and_compile_shader::addFragmentShaderFromSourceCode()
{
	bool success = shader_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragment_shader_source_code);
	if(!success) {
		qDebug() << "vertex";
	}
}

void load_and_compile_shader::clear()
{
	vertex_shader_file->flush();
	vertex_shader_file->close();
	delete vertex_shader_file;
	delete text_stream;
	vertex_shader_source_code.clear();
	fragment_shader_source_code.clear();
	
	
}

QOpenGLShaderProgram * load_and_compile_shader::get_shader_program()
{
	return shader_program;
}

long long int load_and_compile_shader::get_total_bytes_of_shader_file(QString file_location)
{
	long long int output = -1;
	
	total_bytes_shader_file = new QFile(file_location);
	if(total_bytes_shader_file->exists() == false)
	{
		qDebug() << " must be a valid file.";
	}else{
		bool open_success = total_bytes_shader_file->open(QIODevice::ReadOnly | QIODevice::Text);
		if(open_success == false)
		{
			qDebug() << " file unable to open.";
		}else{
			output = (long long int)total_bytes_shader_file->size();
			
		}
	}
	
	total_bytes_shader_file->flush();
	total_bytes_shader_file->close();
	
	delete total_bytes_shader_file;
	
	return output;
}