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
		
		//allocate or write
		/*int * array_of_index = 0; while(array_of_index == 0){ array_of_index = (int*)malloc(2*sizeof(GLfloat));} array_of_index[0] = 0; array_of_index[1] = 1;
		GLfloat * positions_and_colors = list_of_models->value(QString(model_name))->get_combined_tuple(array_of_index);
		long int combined_tuple_size = list_of_models->value(QString(model_name))->get_combined_size(array_of_index);
		free(array_of_index);
		*/
		vbo->allocate(positions_and_colors, combined_tuple_size  * sizeof(GLfloat));
		
		/*QVector3D offset_position_rotation[3];
		offset_position_rotation[0] = QVector3D(list_of_models->value(QString(model_name))->get_x_offset(), list_of_models->value(QString(model_name))->get_y_offset(), list_of_models->value(QString(model_name))->get_z_offset());
		offset_position_rotation[1] = QVector3D(list_of_models->value(QString(model_name))->get_x_rotation(), list_of_models->value(QString(model_name))->get_y_rotation(), list_of_models->value(QString(model_name))->get_z_rotation());
		offset_position_rotation[2] = QVector3D(list_of_models->value(QString(model_name))->get_x_scale(), list_of_models->value(QString(model_name))->get_y_scale(), list_of_models->value(QString(model_name))->get_z_scale());
		*/
		color_shader_program->setUniformValueArray("offset_position_rotation", offset_position_rotation, 3);
		color_shader_program->enableAttributeArray(0);
		color_shader_program->enableAttributeArray(1);
	
		color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
		color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
		glDrawArrays(GL_TRIANGLES, 0, total_points_of_triangles);
		vao->release();
		vbo->release();
		color_shader_program->release();
		
}