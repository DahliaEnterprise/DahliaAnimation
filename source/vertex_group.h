#ifndef VERTEX_GROUP_H
#define VERTEX_GROUP_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <QOpenGLFunctions>
#include <QUrl>
#include <QStringList>
class vertex_group : public QObject
{
    Q_OBJECT
public:
    explicit vertex_group(QObject *parent = nullptr);
		void setPositions(QUrl xyz_file);
		GLfloat * getTrianglePositions();
		unsigned int getTotalTrianglePositions();
		
		void setColors(QUrl file);
		GLfloat * getTriangleColors();
		unsigned int getTotalTriangleColors();
		
		void setCombinedXyzColors(GLfloat * vertex_and_colors, size_t vertex_and_colors_memory_size);
		GLfloat * combined_xyz_colors();
		unsigned int combined_total_xyz_colors();
		
		
		
private:
	GLfloat * triangle_positions;
	unsigned int triangle_positions_memory_size;
	
	GLfloat * triangle_colors;
	unsigned int triangle_colors_memory_size;
	
	GLfloat * triangle_positions_and_colors;
	unsigned int triangle_positions_and_colors_memory_size;
	unsigned short int triangle_positions_and_colors_defined;
	
	QTextStream * text_stream;
	
signals:

};

#endif // VERTEX_GROUP_H
