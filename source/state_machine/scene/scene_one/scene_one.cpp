#include "scene_one.h"

scene_one::scene_one(QObject *parent)
    : QObject{parent}
{
	prestage = 1;
	
	list_of_models = new QMap<QString, state_of_model *>();
	
	
}

int init_square = 1;
int init_triangle = 1;
int flash_square = 0;
void scene_one::iterate()
{
	
	if(prestage == 1)
	{
		tool_model_viewer = new model_viewer();
		
	QFile color_vertex_shader_file("./../DahliaAnimation/source/shader_vertex/color_triangles_test_point_within_vertex.c");
	if(color_vertex_shader_file.exists() == false)
	{
		qDebug() << " must be a valid file.";
	}else{
		bool open_success = color_vertex_shader_file.open(QIODevice::ReadOnly);
		if(open_success == false)
		{
			qDebug() << " file unable to open.";
		}else{
			
		}
	}
	text_stream = new QTextStream();
	text_stream->setDevice(&color_vertex_shader_file);
  QString text_qstring = text_stream->readAll();
    std::string text_stdstring = text_qstring.toUtf8().toStdString();

	color_shader_program = new QOpenGLShaderProgram();
    bool success = color_shader_program->addShaderFromSourceCode(QOpenGLShader::Vertex, text_stdstring.c_str());
	if(!success) {
		qDebug() << "vertex";
	}
	
	delete text_stream;
	
	QFile color_fragment_shader_file("./../DahliaAnimation/source/shader_fragment/color_triangles_test_point_within_vertex_fragment.c");
	if(color_fragment_shader_file.exists() == false)
	{
		qDebug() << " must be a valid file.";
	}else{
		bool open_success = color_fragment_shader_file.open(QIODevice::ReadOnly);
		if(open_success == false)
		{
			qDebug() << " file unable to open.";
		}else{
			
		}
	}
	text_stream = new QTextStream();
	text_stream->setDevice(&color_fragment_shader_file);
  text_qstring = text_stream->readAll();
	
  text_stdstring = text_qstring.toUtf8().toStdString();
	
	success = color_shader_program->addShaderFromSourceCode(QOpenGLShader::Fragment, text_stdstring.c_str());
	if(!success) {
		qDebug() << "fragment";
	}
	
		
		init_square = 1;
		color_shader_program->bind();
		
		QOpenGLVertexArrayObject * square_ogl_vao_quad = new QOpenGLVertexArrayObject();
		square_ogl_vao_quad->create();
		square_ogl_vao_quad->bind();
		
		QOpenGLBuffer * square_ogl_vbo_quad = new QOpenGLBuffer();
		square_ogl_vbo_quad->create();
		square_ogl_vbo_quad->setUsagePattern(QOpenGLBuffer::StaticDraw);
		square_ogl_vbo_quad->bind();
		
		color_shader_program->enableAttributeArray(0);
		color_shader_program->enableAttributeArray(1);
		color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
		color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
		
		state_of_model * square_model_state_information = new state_of_model();
		square_model_state_information->initialize(2);
		square_model_state_information->load_vertex_positions(QString("./../DahliaAnimation/source/vertex/square.xyz"));
		square_model_state_information->load_vertex_colors(QString("./../DahliaAnimation/source/vertex_color/square.rgb"));
		//model_information->add_model(QString("square"), square_model_state_information);
		list_of_models->insert("square", square_model_state_information);
		
		
		
		//associate vao and vbo.
		list_of_models->value(QString("square"))->associate_vao(square_ogl_vao_quad);
		list_of_models->value(QString("square"))->associate_vbo(square_ogl_vbo_quad);
		
			//clean/clear
			square_ogl_vao_quad->release();
			square_ogl_vbo_quad->release();
			color_shader_program->release();
		
		
		color_shader_program->bind();
		
		QOpenGLVertexArrayObject * triangle_ogl_vao_quad = new QOpenGLVertexArrayObject();
		triangle_ogl_vao_quad->create();
		triangle_ogl_vao_quad->bind();
		
		QOpenGLBuffer * triangle_ogl_vbo_quad = new QOpenGLBuffer();
		triangle_ogl_vbo_quad->create();
		triangle_ogl_vbo_quad->setUsagePattern(QOpenGLBuffer::StaticDraw);
		triangle_ogl_vbo_quad->bind();
		
		color_shader_program->enableAttributeArray(0);
		color_shader_program->enableAttributeArray(1);
		color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
		color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
		
		state_of_model * triangle_model_state_information = new state_of_model();
		triangle_model_state_information->initialize(2);
		triangle_model_state_information->load_vertex_positions(QString("./../DahliaAnimation/source/vertex/triangle.xyz"));
		triangle_model_state_information->load_vertex_colors(QString("./../DahliaAnimation/source/vertex_color/triangle.rgb"));
		//model_information->add_model(QString("triangle"), triangle_model_state_information);
		list_of_models->insert("triangle", triangle_model_state_information);
		
		
		
		//associate vao and vbo.
		list_of_models->value(QString("triangle"))->associate_vao(triangle_ogl_vao_quad);
		list_of_models->value(QString("triangle"))->associate_vbo(triangle_ogl_vbo_quad);
		
			//clean/clear
			triangle_ogl_vao_quad->release();
			triangle_ogl_vbo_quad->release();
			color_shader_program->release();
			
	
		prestage = 0;
	}else if(prestage == 0)
	{
	
	  if(flash_square == 0)
		{
			flash_square = 1;
			
		}else{
			flash_square = 0;
			
		}
	
		list_of_models->value("square")->set_flag_render_model(flash_square);
		
		list_of_models->value("triangle")->set_flag_render_model(1);
		
		//list_of_models->value("triangle")->rotate(0.0, 0.0, 0.1);
		
	}
	//offset
	//list_of_models->value("square")->translate(0.001, 0.0, 0.0);
	//list_of_models->value("square")->rotate(0.0, 0.0, 0.01);
	
	

}

void scene_one::associate_color_shader(QOpenGLShaderProgram * set_color_shader_program)
{
	color_shader_program = set_color_shader_program;
}


void scene_one::render()
{
	
	QOpenGLVertexArrayObject * vao = list_of_models->value("square")->get_vao();
	QOpenGLBuffer * vbo = list_of_models->value("square")->get_vbo();
		
	//draw_arrays_using_color_shader((char*)"square", vao, vbo, 6);
	int * array_of_index = 0; while(array_of_index == 0){ array_of_index = (int*)malloc(2*sizeof(GLfloat));} array_of_index[0] = 0; array_of_index[1] = 1;
	GLfloat * positions_and_colors = list_of_models->value(QString("square"))->get_combined_tuple(array_of_index);
	long int combined_tuple_size = list_of_models->value(QString("square"))->get_combined_size(array_of_index);
	free(array_of_index);
	
	QVector3D offset_position_rotation[3];
	offset_position_rotation[0] = QVector3D(list_of_models->value(QString("square"))->get_x_offset(), list_of_models->value(QString("square"))->get_y_offset(), list_of_models->value(QString("square"))->get_z_offset());
	offset_position_rotation[1] = QVector3D(list_of_models->value(QString("square"))->get_x_rotation(), list_of_models->value(QString("square"))->get_y_rotation(), list_of_models->value(QString("square"))->get_z_rotation());
	offset_position_rotation[2] = QVector3D(list_of_models->value(QString("square"))->get_x_scale(), list_of_models->value(QString("square"))->get_y_scale(), list_of_models->value(QString("square"))->get_z_scale());
		
	tool_model_viewer->render(positions_and_colors, combined_tuple_size, vao, vbo, color_shader_program,  6, offset_position_rotation);

	
	vao = list_of_models->value("triangle")->get_vao();
	vbo = list_of_models->value("triangle")->get_vbo();
	
	//draw_arrays_using_color_shader((char*)"triangle", vao, vbo, 6);
	
	/*int	triangle_do_render = list_of_models->value(QString("triangle"))->get_flag_render_model();
	if(triangle_do_render == 1)
	{
		QOpenGLVertexArrayObject * vao = list_of_models->value("triangle")->get_vao();
		QOpenGLBuffer * vbo = list_of_models->value("triangle")->get_vbo();
		
		int triangle_do_write_vbo = list_of_models->value(QString("triangle"))->get_flag_vbo();
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
			GLfloat * positions_and_colors = list_of_models->value(QString("triangle"))->get_combined_tuple(array_of_index);
			long int combined_tuple_size = list_of_models->value(QString("triangle"))->get_combined_size(array_of_index);
			free(array_of_index);
			//qDebug() << "tuple sizs" << combined_tuple_size;
		//	if(init_triangle == 1)
		//	{
		//	if(list_of_models->value("triangle")->get_flag_allocate() == 1)
		//	{
				vbo->allocate(positions_and_colors, combined_tuple_size  * sizeof(GLfloat));
				//list_of_models->value(QString("triangle"))->scale(0.5, 0.5, 0.5);
				//list_of_models->value(QString("triangle"))->translate(0.5, 0.5, 0.5);
				list_of_models->value("triangle")->set_flag_allocate(0);
		//	}
			//}
			
			QVector3D offset_position_rotation[3];
			offset_position_rotation[0] = QVector3D(list_of_models->value(QString("triangle"))->get_x_offset(), list_of_models->value(QString("triangle"))->get_y_offset(), list_of_models->value(QString("triangle"))->get_z_offset());
			offset_position_rotation[1] = QVector3D(list_of_models->value(QString("triangle"))->get_x_rotation(), list_of_models->value(QString("triangle"))->get_y_rotation(), list_of_models->value(QString("triangle"))->get_z_rotation());
			offset_position_rotation[2] = QVector3D(list_of_models->value(QString("triangle"))->get_x_scale(), list_of_models->value(QString("triangle"))->get_y_scale(), list_of_models->value(QString("triangle"))->get_z_scale());
			
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
	}*/
}

void scene_one::draw_arrays_using_color_shader(char * model_name, QOpenGLVertexArrayObject * vao, QOpenGLBuffer * vbo, int total_points_of_triangles)
{
	int	do_render = list_of_models->value(QString(model_name))->get_flag_render_model();
	if(do_render == 1)
	{
		color_shader_program->bind();
		vao->bind();
		vbo->bind();
		vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
		
		//allocate or write
		int * array_of_index = 0; while(array_of_index == 0){ array_of_index = (int*)malloc(2*sizeof(GLfloat));} array_of_index[0] = 0; array_of_index[1] = 1;
		GLfloat * positions_and_colors = list_of_models->value(QString(model_name))->get_combined_tuple(array_of_index);
		long int combined_tuple_size = list_of_models->value(QString(model_name))->get_combined_size(array_of_index);
		free(array_of_index);
		vbo->allocate(positions_and_colors, combined_tuple_size  * sizeof(GLfloat));
		
		QVector3D offset_position_rotation[3];
		offset_position_rotation[0] = QVector3D(list_of_models->value(QString(model_name))->get_x_offset(), list_of_models->value(QString(model_name))->get_y_offset(), list_of_models->value(QString(model_name))->get_z_offset());
		offset_position_rotation[1] = QVector3D(list_of_models->value(QString(model_name))->get_x_rotation(), list_of_models->value(QString(model_name))->get_y_rotation(), list_of_models->value(QString(model_name))->get_z_rotation());
		offset_position_rotation[2] = QVector3D(list_of_models->value(QString(model_name))->get_x_scale(), list_of_models->value(QString(model_name))->get_y_scale(), list_of_models->value(QString(model_name))->get_z_scale());
		
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
}



