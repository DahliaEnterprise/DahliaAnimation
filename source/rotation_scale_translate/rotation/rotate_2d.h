#ifndef ROTATE_2D_H
#define ROTATE_2D_H

#include <QObject>
#include <GL/gl.h>
	#include <QtMath>
#include <QDebug>


class rotate_2d : public QObject
{
    Q_OBJECT
public:
    explicit rotate_2d(QObject *parent = nullptr);
		
		GLfloat * rotate_x(GLfloat * vertex, size_t vertex_memory_size, GLfloat offset_x_rotation);
		
		GLfloat * rotate_y(GLfloat * vertex, size_t vertex_memory_size, GLfloat offset_y_rotation);
		
		GLfloat *  get_two_dimensional_adjacent_opposite_hypotenus(GLfloat point_one_x, GLfloat point_one_y, GLfloat point_two_x, GLfloat point_two_y);
		
		GLfloat get_two_dimensional_angle_as_radians(GLfloat adjacent, GLfloat hypotenus, GLfloat point_one_x, GLfloat point_one_y, GLfloat point_two_x, GLfloat point_two_y);
		
		GLfloat * get_two_dimensional_apply_desired_rotation(GLfloat current_angle_as_radians, GLfloat offset_angle_as_radians, GLfloat hypotenus);
		
		
private:
	
signals:

};

#endif // ROTATE_2D_H
