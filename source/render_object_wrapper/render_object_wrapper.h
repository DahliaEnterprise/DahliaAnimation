#ifndef RENDER_OBJECT_WRAPPER_H
#define RENDER_OBJECT_WRAPPER_H

#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class render_object_wrapper : public QObject
{
    Q_OBJECT
public:
    explicit render_object_wrapper(QObject *parent = nullptr);

		void set_vao_vbo(QOpenGLVertexArrayObject incoming_vao_quad, QOpenGLBuffer * incoming_vbo_quad);
		
		QOpenGLVertexArrayObject get_vao();
		QOpenGLBuffer * get_vbo();
		
private:
	QOpenGLVertexArrayObject vao_quad;
	QOpenGLBuffer * vbo_quad;
  
		
signals:

};

#endif // RENDER_OBJECT_WRAPPER_H
