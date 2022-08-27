#include "render_object_wrapper.h"

render_object_wrapper::render_object_wrapper(QObject *parent)
    : QObject{parent}
{

}

void render_object_wrapper::set_vao_vbo(QOpenGLVertexArrayObject incoming_vao_quad, QOpenGLBuffer * incoming_vbo_quad);
{
	vao_quad = incoming_vao_quad;
	vbo_quad = incoming_vbo_quad;
}

QOpenGLVertexArrayObject render_object_wrapper::get_vao()
{
	return vao_quad;
}

QOpenGLBuffer * render_object_wrapper::get_vbo();
{
	return vbo_quad;
}
		
		