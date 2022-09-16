#ifndef TUPLE_FLOAT_H
#define TUPLE_FLOAT_H

#include <QObject>
#include <QOpenGLWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLPaintDevice>
#include <QFile>

class tuple_float : public QObject
{
    Q_OBJECT
public:
    explicit tuple_float(QObject *parent = nullptr);
		void initialize(int array_size);
		int setFloatArray_by_file(int tuple_index, QString filelocation);
		GLfloat * get_combined_tuple(int * array_of_tuple_index, int * array_of_vector_size);
		long int get_combined_size(int * array_of_tuple_index);

private:
		int array_size_of_tuple;
		GLfloat * array_of_floats_index_zero;
		int array_of_floats_index_zero_size;
		
		GLfloat * array_of_floats_index_one;
		int array_of_floats_index_one_size;
		
		QFile * longterm_storage;
		QTextStream * longterm_storage_text_stream;
		
signals:

};

#endif // TUPLE_FLOAT_H
