#include "model_viewer.h"

model_viewer::model_viewer(QObject *parent)
    : QObject{parent}
{

}

void model_viewer::render(GLfloat * positions_and_colors, long int combined_tuple_size, QOpenGLVertexArrayObject * vao, QOpenGLBuffer * vbo, QOpenGLShaderProgram * color_shader_program, int total_points_of_triangles, QVector3D offset_position_rotation[3])
{
		color_shader_program->bind();
		vao->bind();
		vbo->bind();
		vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
		
		vbo->allocate(positions_and_colors, combined_tuple_size  * sizeof(GLfloat));
	
		color_shader_program->setUniformValueArray("offset_position_rotation", offset_position_rotation, 3);
		color_shader_program->enableAttributeArray(0);
		color_shader_program->enableAttributeArray(1);
	
		color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
		color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
		glDrawArrays(GL_TRIANGLES, 0, total_points_of_triangles);
		vao->release();
		vbo->release();
		color_shader_program->release();
		
		color_shader_program->bind();
		vao->bind();
		vbo->bind();
		vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
		
		vbo->allocate(positions_and_colors, combined_tuple_size  * sizeof(GLfloat));
	
		color_shader_program->setUniformValueArray("offset_position_rotation", offset_position_rotation, 3);
		color_shader_program->enableAttributeArray(0);
		color_shader_program->enableAttributeArray(1);
	
		color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
		color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
		//glDrawArrays(GL_LINES, 0, total_points_of_triangles);
		vao->release();
		vbo->release();
		color_shader_program->release();
		
}