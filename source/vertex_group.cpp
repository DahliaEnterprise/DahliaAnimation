#include "vertex_group.h"

vertex_group::vertex_group(QObject *parent) : QObject(parent)
{
triangle_positions_and_colors_defined = 0;
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

void vertex_group::setColors(QUrl file)
{
	QFile colors(file.path());
	if(colors.exists() == false)
	{
		qDebug() << "colors must be a valid file.";
	}else{
		bool open_success = colors.open(QIODevice::ReadOnly);
		if(open_success == false)
		{
			qDebug() << "position file unable to open.";
		}else{
			text_stream = new QTextStream();
			text_stream->setDevice(&colors);
			QString text = text_stream->readAll();
			QStringList text_parts = text.split(QString(","));
			triangle_colors = 0; while(triangle_colors == 0){ triangle_colors = (GLfloat*)malloc(text_parts.size() * sizeof(GLfloat)); }
			triangle_colors_memory_size = text_parts.size();
			int index = 0;
			while(index < text_parts.size())
			{
				//
				double planer_value = text_parts.at(index).toDouble();
				triangle_colors[index] = (GLfloat)planer_value;
				
				//
				index = index + 1;
			}
			
			
			delete text_stream;
			
			
		}
		
		colors.flush();
		colors.close();
	}
}

GLfloat * vertex_group::getTriangleColors()
{
	return triangle_colors;
}

unsigned int vertex_group::getTotalTriangleColors()
{
	return triangle_colors_memory_size;
}

GLfloat * vertex_group::combined_xyz_colors()
{
	if(triangle_positions_and_colors_defined == 0)
	{
		triangle_positions_and_colors_memory_size =  triangle_positions_memory_size + triangle_colors_memory_size;
		triangle_positions_and_colors = 0; while(triangle_positions_and_colors == 0){ triangle_positions_and_colors = (GLfloat*)malloc(triangle_positions_and_colors_memory_size * sizeof(GLfloat)); }
		unsigned int index = 0;
		unsigned int position_index = 0;
		unsigned int color_index = 0;
		
		while(index < triangle_positions_and_colors_memory_size)
		{
			triangle_positions_and_colors[index] = triangle_positions[position_index];
			triangle_positions_and_colors[index+1] = triangle_positions[position_index+1];
			triangle_positions_and_colors[index+2] = triangle_positions[position_index+2];
			
			triangle_positions_and_colors[index+3] = triangle_colors[color_index];
			triangle_positions_and_colors[index+4] = triangle_colors[color_index+1];
			triangle_positions_and_colors[index+5] = triangle_colors[color_index+2];
			
			index = index + 6;
			position_index = position_index + 3;
			color_index = color_index + 3;
			if(index >= triangle_positions_and_colors_memory_size)
			{
				index = triangle_positions_and_colors_memory_size;
			}
		}
		
		triangle_positions_and_colors_defined = 1;
	}
		return triangle_positions_and_colors;

}

void vertex_group::setCombinedXyzColors(GLfloat * vertex_and_colors, size_t vertex_and_colors_memory_size)
{
	triangle_positions_and_colors = vertex_and_colors;
	triangle_positions_and_colors_memory_size = vertex_and_colors_memory_size;
	triangle_positions_and_colors_defined = 1;
}



unsigned int vertex_group::combined_total_xyz_colors()
{
	return triangle_positions_and_colors_memory_size;
}
	