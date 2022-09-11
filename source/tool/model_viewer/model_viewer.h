#ifndef MODEL_VIEWER_H
#define MODEL_VIEWER_H

#include <QObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
class model_viewer : public QObject
{
    Q_OBJECT
public:
    explicit model_viewer(QObject *parent = nullptr);
		
		void render(GLfloat * positions_and_colors, long int combined_tuple_size, QOpenGLVertexArrayObject * vao, QOpenGLBuffer * vbo, QOpenGLShaderProgram * color_shader_program, int total_points_of_triangles, QVector3D offset_position_rotation[3]);
		
signals:

};

#endif // MODEL_VIEWER_H
