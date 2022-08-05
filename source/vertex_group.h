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
		
private:
	GLfloat * triangle_positions;
	unsigned int triangle_positions_memory_size;
	
	QTextStream * text_stream;
	
signals:

};

#endif // VERTEX_GROUP_H
