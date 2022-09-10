#include "scene_one.h"

scene_one::scene_one(QObject *parent)
    : QObject{parent}
{

}

void scene_one::initialize()
{
	
}

int flash_square = 0;
void scene_one::iterate(models * model_information)
{
	if(flash_square == 0)
	{
		flash_square = 1;
		
	}else{
		flash_square = 0;
		
	}

	model_information->get_state_of_models()->value("square")->set_flag_render_model(flash_square);
	model_information->get_state_of_models()->value("square")->set_flag_vbo();
	
	model_information->get_state_of_models()->value("triangle")->set_flag_render_model(1);
	model_information->get_state_of_models()->value("triangle")->set_flag_vbo();
	
	model_information->get_state_of_models()->value("triangle")->rotate(0.0, 0.0, 0.1);
	
	
	//offset
	//model_information->get_state_of_models()->value("square")->translate(0.001, 0.0, 0.0);
	//model_information->get_state_of_models()->value("square")->rotate(0.0, 0.0, 0.01);
	
	

}

void scene_one::associate_color_shader(QOpenGLShaderProgram * set_color_shader_program)
{
	color_shader_program = set_color_shader_program;
}

int init_square = 1;
int init_triangle = 1;
void scene_one::render(models * model_information)
{
	int	square_do_render = model_information->get_state_of_models()->value(QString("square"))->get_flag_render_model();
	if(square_do_render == 1)
	{
		QOpenGLVertexArrayObject * vao = model_information->get_state_of_models()->value("square")->get_vao();
		QOpenGLBuffer * vbo = model_information->get_state_of_models()->value("square")->get_vbo();
		color_shader_program->bind();
		vao->bind();
		vbo->bind();
		vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
		
		//allocate or write
		int * array_of_index = 0; while(array_of_index == 0){ array_of_index = (int*)malloc(2*sizeof(GLfloat));} array_of_index[0] = 0; array_of_index[1] = 1;
		GLfloat * positions_and_colors = model_information->get_state_of_models()->value(QString("square"))->get_combined_tuple(array_of_index);
		long int combined_tuple_size = model_information->get_state_of_models()->value(QString("square"))->get_combined_size(array_of_index);
		free(array_of_index);
		if(init_square == 1)
		{
			vbo->allocate(positions_and_colors, combined_tuple_size  * sizeof(GLfloat));
			init_square = 0;
		}
		
		QVector3D offset_position_rotation[3];
		offset_position_rotation[0] = QVector3D(model_information->get_state_of_models()->value(QString("square"))->get_x_offset(), model_information->get_state_of_models()->value(QString("square"))->get_y_offset(), model_information->get_state_of_models()->value(QString("square"))->get_z_offset());
		offset_position_rotation[1] = QVector3D(model_information->get_state_of_models()->value(QString("square"))->get_x_rotation(), model_information->get_state_of_models()->value(QString("square"))->get_y_rotation(), model_information->get_state_of_models()->value(QString("square"))->get_z_rotation());
		offset_position_rotation[2] = QVector3D(model_information->get_state_of_models()->value(QString("square"))->get_x_scale(), model_information->get_state_of_models()->value(QString("square"))->get_y_scale(), model_information->get_state_of_models()->value(QString("square"))->get_z_scale());
		
		color_shader_program->setUniformValueArray("offset_position_rotation", offset_position_rotation, 3);
		int square_do_write_vbo = model_information->get_state_of_models()->value(QString("square"))->get_flag_vbo();
		if(square_do_write_vbo == 1)
		{
			//write
			vbo->write(0, positions_and_colors, combined_tuple_size  * sizeof(GLfloat));
		}
		color_shader_program->enableAttributeArray(0);
		color_shader_program->enableAttributeArray(1);
	
		color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
		color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
		glDrawArrays(GL_TRIANGLES, 0, 6);
		vao->release();
		vbo->release();
		color_shader_program->release();
		
	}
	
	int	triangle_do_render = model_information->get_state_of_models()->value(QString("triangle"))->get_flag_render_model();
	if(triangle_do_render == 1)
	{
		QOpenGLVertexArrayObject * vao = model_information->get_state_of_models()->value("triangle")->get_vao();
		QOpenGLBuffer * vbo = model_information->get_state_of_models()->value("triangle")->get_vbo();
		
		int triangle_do_write_vbo = model_information->get_state_of_models()->value(QString("triangle"))->get_flag_vbo();
		if(triangle_do_write_vbo == 1)
		{
			color_shader_program->bind();
			vao->bind();
			vbo->bind();
			vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
			
			//allocate or write
			int * array_of_index = 0; while(array_of_index == 0){ array_of_index = (int*)malloc(2*sizeof(GLfloat));}
			array_of_index[0] = 0;
			array_of_index[1] = 1;
			GLfloat * positions_and_colors = model_information->get_state_of_models()->value(QString("triangle"))->get_combined_tuple(array_of_index);
			long int combined_tuple_size = model_information->get_state_of_models()->value(QString("triangle"))->get_combined_size(array_of_index);
			free(array_of_index);
//qDebug() << "tuple sizs" << combined_tuple_size;
			if(init_triangle == 1)
			{
				vbo->allocate(positions_and_colors, combined_tuple_size  * sizeof(GLfloat));
				model_information->get_state_of_models()->value(QString("triangle"))->scale(0.5, 0.5, 0.5);
				model_information->get_state_of_models()->value(QString("triangle"))->translate(0.5, 0.5, 0.5);
				init_triangle = 0;
			}
			
			QVector3D offset_position_rotation[3];
			offset_position_rotation[0] = QVector3D(model_information->get_state_of_models()->value(QString("triangle"))->get_x_offset(), model_information->get_state_of_models()->value(QString("triangle"))->get_y_offset(), model_information->get_state_of_models()->value(QString("triangle"))->get_z_offset());
			offset_position_rotation[1] = QVector3D(model_information->get_state_of_models()->value(QString("triangle"))->get_x_rotation(), model_information->get_state_of_models()->value(QString("triangle"))->get_y_rotation(), model_information->get_state_of_models()->value(QString("triangle"))->get_z_rotation());
			offset_position_rotation[2] = QVector3D(model_information->get_state_of_models()->value(QString("triangle"))->get_x_scale(), model_information->get_state_of_models()->value(QString("triangle"))->get_y_scale(), model_information->get_state_of_models()->value(QString("triangle"))->get_z_scale());
			
			color_shader_program->setUniformValueArray("offset_position_rotation", offset_position_rotation, 3);
			
			//write
			vbo->write(0, positions_and_colors, combined_tuple_size  * sizeof(GLfloat));
			
		
			color_shader_program->enableAttributeArray(0);
			color_shader_program->enableAttributeArray(1);
		
			color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
			color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
			glDrawArrays(GL_TRIANGLES, 0, 6);
			vao->release();
			vbo->release();
			color_shader_program->release();
		}
	}
}