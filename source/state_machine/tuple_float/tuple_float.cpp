#include "tuple_float.h"

tuple_float::tuple_float(QObject *parent)
    : QObject{parent}
{

}

void tuple_float::initialize(int array_size)
{
	array_size_of_tuple = array_size;
	
}

int tuple_float::setFloatArray_by_file(int tuple_index, QString filelocation)
{
	int output = -1;
	
	longterm_storage = new QFile(filelocation);
	if(longterm_storage->exists() == false)
	{
		qDebug() << "positions must be a valid file.";
		output = -2;
	}else{
		bool open_success = longterm_storage->open(QIODevice::ReadOnly);
		if(open_success == false)
		{
			qDebug() << "position file unable to open.";
		}else{
			longterm_storage_text_stream = new QTextStream();
			longterm_storage_text_stream->setDevice(longterm_storage);
			QString text = longterm_storage_text_stream->readAll();
			
			QStringList array_of_decimals = text.split(",");
			if(tuple_index == 0)
			{
				array_of_floats_index_zero = 0; while(array_of_floats_index_zero == 0){ array_of_floats_index_zero = (GLfloat *)malloc(array_of_decimals.size() * sizeof(GLfloat)); }
				int array_index = 0;
				while(array_index < array_of_decimals.size())
				{
					array_of_floats_index_zero[array_index] = 0.0;
					
					
					array_index = array_index + 1;
				}
				int index = 0;
				while(index < array_of_decimals.size())
				{
					QString decimal_as_string = array_of_decimals.at(index).trimmed();
					GLfloat decimal = (GLfloat)decimal_as_string.toFloat();
					array_of_floats_index_zero[index] = decimal;
					//qDebug() << array_of_floats_index_zero[index];
					index = index + 1;
				}
				array_of_floats_index_zero_size = array_of_decimals.size();
			}else if(tuple_index == 1)
			{
				array_of_floats_index_one = 0; while(array_of_floats_index_one == 0){ array_of_floats_index_one = (GLfloat *)malloc(array_of_decimals.size() * sizeof(GLfloat)); }
				int array_index = 0;
				while(array_index < array_of_decimals.size())
				{
					array_of_floats_index_one[array_index] = 0.0;
					
					
					array_index = array_index + 1;
				}
				int index = 0;
				while(index < array_of_decimals.size())
				{
					QString decimal_as_string = array_of_decimals.at(index).trimmed();
					GLfloat decimal = (GLfloat)decimal_as_string.toFloat();
					array_of_floats_index_one[index] = decimal;
//	qDebug() << array_of_floats_index_one[index];
					index = index + 1;
				}
				array_of_floats_index_one_size = array_of_decimals.size();
				
			}
			
			
			delete longterm_storage_text_stream;
			
			longterm_storage->flush();
			longterm_storage->close();
		}
		
	}
	delete longterm_storage;
	
	return output;
}

GLfloat * tuple_float::get_combined_tuple(int * array_of_tuple_index)
{
	GLfloat * output = 0;
	
	
	long int combined_selected_floatarrays = 0;
	
	if(array_of_tuple_index[0] == 0 || array_of_tuple_index[1] == 0)
	{
		combined_selected_floatarrays += array_of_floats_index_zero_size;
	}
	
	if(array_of_tuple_index[0] == 1 || array_of_tuple_index[1] == 1)
	{
		combined_selected_floatarrays += array_of_floats_index_one_size;
	}
	
	while(output == 0){ output = (GLfloat *)malloc(combined_selected_floatarrays * sizeof(GLfloat));}
	
	unsigned int index = 0;
	unsigned int tuple_one_index = 0;
	unsigned int tuple_two_index = 0;
	
	while(index < combined_selected_floatarrays)
	{
		if(array_of_tuple_index[0] == 0 || array_of_tuple_index[1] == 0)
		{
			output[index] = array_of_floats_index_zero[tuple_one_index];
			output[index+1] = array_of_floats_index_zero[tuple_one_index+1];
			output[index+2] = array_of_floats_index_zero[tuple_one_index+2];
			/*qDebug() << output[index];
			qDebug() << output[index+1];
			qDebug() << output[index+2];
			*/
		}
		
		if(array_of_tuple_index[0] == 1 || array_of_tuple_index[1] == 1)
		{
			output[index+3] = array_of_floats_index_one[tuple_two_index];
			output[index+4] = array_of_floats_index_one[tuple_two_index+1];
			output[index+5] = array_of_floats_index_one[tuple_two_index+2];
	/*	qDebug() << output[index];
			qDebug() << output[index+1];
			qDebug() << output[index+2];
			*/
		
			
		}
		
		index = index + (array_size_of_tuple * 3);
		if(array_of_tuple_index[0] == 0 || array_of_tuple_index[1] == 0)
		{
			tuple_one_index = tuple_one_index + 3;
		}
		
		if(array_of_tuple_index[0] == 1 || array_of_tuple_index[1] == 1)
		{
			tuple_two_index = tuple_two_index + 3;
		}
	}
	return output;
}

long int tuple_float::get_combined_size(int * array_of_tuple_index)
{
	long int combined_selected_floatarrays = 0;
	
	if(array_of_tuple_index[0] == 0 || array_of_tuple_index[1] == 0)
	{
		combined_selected_floatarrays += array_of_floats_index_zero_size;
	}
	
	if(array_of_tuple_index[0] == 1 || array_of_tuple_index[1] == 1)
	{
		combined_selected_floatarrays += array_of_floats_index_one_size;
	}
	
	
	return combined_selected_floatarrays;
}