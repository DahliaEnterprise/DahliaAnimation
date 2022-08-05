#include "vertex_group.h"

vertex_group::vertex_group(QObject *parent) : QObject(parent)
{

}

void vertex_group::setPositions(QUrl xyz_file)
{
	QFile positions(xyz_file.path());
	if(positions.exists() == false)
	{
		qDebug() << "positions must be a valid file.";
	}else{
		bool open_success = positions.open(QIODevice::ReadOnly);
		if(open_success == false)
		{
			qDebug() << "position file unable to open.";
		}else{
			text_stream = new QTextStream();
			text_stream->setDevice(&positions);
			QString text = text_stream->readAll();
			QStringList text_parts = text.split(QString(","));
			triangle_positions = 0; while(triangle_positions == 0){ triangle_positions = (GLfloat*)malloc(text_parts.size() * sizeof(GLfloat)); }
			triangle_positions_memory_size = text_parts.size();
			int index = 0;
			while(index < text_parts.size())
			{
				//
				double planer_value = text_parts.at(index).toDouble();
				triangle_positions[index] = (GLfloat)planer_value;
				
				//
				index = index + 1;
			}
			
			
			delete text_stream;
			
			
		}
		
		positions.flush();
		positions.close();
	}
}

GLfloat * vertex_group::getTrianglePositions()
{
	return triangle_positions;
}

unsigned int vertex_group::getTotalTrianglePositions()
{
	return triangle_positions_memory_size;
}
