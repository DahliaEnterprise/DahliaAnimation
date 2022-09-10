#include "openglwindows.h"

openglwindows::openglwindows()
{

}


void openglwindows::initializeGL()
{
	
	stoplight_positions_vertex_group = new vertex_group();
	stoplight_positions_vertex_group->setPositions(QUrl("./../DahliaAnimation/source/stoplightray_balls/triangle.xyz"));
	
	
	statemachine = new state_machine();
	statemachine->initialize();
	ptr_to_state_of_models = statemachine->get_model_information()->get_state_of_models();
	
	
  initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 1.0f, 0.9f);
	qDebug() << "initializing";
	
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
	
	//associate color program
	statemachine->get_game_information()->associate_color_shader(color_shader_program);
	
	
	//initialize resources.
		//init square
		init_square = 1;
		color_shader_program->bind();
		
		square_ogl_vao_quad = new QOpenGLVertexArrayObject();
		square_ogl_vao_quad->create();
		square_ogl_vao_quad->bind();
		
		square_ogl_vbo_quad = new QOpenGLBuffer();
		square_ogl_vbo_quad->create();
		square_ogl_vbo_quad->setUsagePattern(QOpenGLBuffer::StaticDraw);
		square_ogl_vbo_quad->bind();
		//square_ogl_vbo_quad->allocate(square_vertex_and_colors->combined_xyz_colors(), square_vertex_and_colors->combined_total_xyz_colors() * sizeof(GLfloat));
			
		color_shader_program->enableAttributeArray(0);
		color_shader_program->enableAttributeArray(1);
		color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
		color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
		
		state_of_model * square_model_state_information = new state_of_model();
		square_model_state_information->initialize(2);
		square_model_state_information->load_vertex_positions(QString("./../DahliaAnimation/source/vertex/square.xyz"));
		square_model_state_information->load_vertex_colors(QString("./../DahliaAnimation/source/vertex_color/square.rgb"));
		statemachine->get_model_information()->add_model(QString("square"), square_model_state_information);
		
		//associate vao and vbo.
		ptr_to_state_of_models->value(QString("square"))->associate_vao(square_ogl_vao_quad);
		ptr_to_state_of_models->value(QString("square"))->associate_vbo(square_ogl_vbo_quad);
		
			//clean/clear
			square_ogl_vao_quad->release();
			square_ogl_vbo_quad->release();
			color_shader_program->release();
			
		//init triangle
		init_triangle = 1;
		color_shader_program->bind();
		triangle_ogl_vao_quad.create();
		triangle_ogl_vao_quad.bind();
		
		triangle_ogl_vbo_quad = new QOpenGLBuffer();
		triangle_ogl_vbo_quad->create();
		triangle_ogl_vbo_quad->setUsagePattern(QOpenGLBuffer::StaticDraw);
		triangle_ogl_vbo_quad->bind();
		//triangle_ogl_vbo_quad->allocate(triangle_vertex_and_colors_altered->combined_xyz_colors(), triangle_vertex_and_colors_altered->combined_total_xyz_colors() * sizeof(GLfloat));
			
		color_shader_program->enableAttributeArray(0);
		color_shader_program->enableAttributeArray(1);
		color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
		color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
		
		state_of_model * triangle_model_state_information = new state_of_model();
		triangle_model_state_information->initialize(2);
		triangle_model_state_information->load_vertex_positions(QString("./../DahliaAnimation/source/vertex/triangle.xyz"));
		triangle_model_state_information->load_vertex_colors(QString("./../DahliaAnimation/source/vertex_color/triangle.rgb"));
		statemachine->get_model_information()->add_model(QString("triangle"), triangle_model_state_information);
		
		
			//clean/clear
			triangle_ogl_vao_quad.release();
			triangle_ogl_vbo_quad->release();
			color_shader_program->release();
			
			
		
		//start painting
		qDebug() << "run";
		QTimer::singleShot(200, this, SLOT(run_paint()));
		
}
 
void openglwindows::resizeGL(int width, int height)
{
  (void)width;
  (void)height;
}
 
void openglwindows::paintGL()
{
	
}
 
void openglwindows::run_paint()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	  //load shadow balls
		GLfloat * stoplight_positions = stoplight_positions_vertex_group->getTrianglePositions();
		
		QVector3D stoplight_points[stoplight_positions_vertex_group->getTotalTrianglePositions()];
		unsigned int index = 0;
		unsigned int stoplight_points_index = 0;
		while(index < stoplight_positions_vertex_group->getTotalTrianglePositions())
		{
			stoplight_points[stoplight_points_index] = QVector3D(stoplight_positions[index], stoplight_positions[index+1], stoplight_positions[index+2]);
			
			stoplight_points_index = stoplight_points_index + 1;
			index = index + 3;
		}
		
		statemachine->get_game_information()->scene_iterate();
		
		statemachine->get_game_information()->render();
		
		//square (ground)
		
		/*int	square_do_render = ptr_to_state_of_models->value(QString("square"))->get_flag_render_model();
		if(square_do_render == 1)
		{
			
			color_shader_program->bind();
			square_ogl_vao_quad->bind();
			square_ogl_vbo_quad->bind();
			square_ogl_vbo_quad->setUsagePattern(QOpenGLBuffer::StaticDraw);
			
			//allocate or write
			int * array_of_index = 0; while(array_of_index == 0){ array_of_index = (int*)malloc(2*sizeof(GLfloat));} array_of_index[0] = 0; array_of_index[1] = 1;
			GLfloat * positions_and_colors = ptr_to_state_of_models->value(QString("square"))->get_combined_tuple(array_of_index);
			long int combined_tuple_size = ptr_to_state_of_models->value(QString("square"))->get_combined_size(array_of_index);
			free(array_of_index);
			if(init_square == 1)
			{
				square_ogl_vbo_quad->allocate(positions_and_colors, combined_tuple_size  * sizeof(GLfloat));
				init_square = 0;
			}
			
			QVector3D offset_position_rotation[3];
			offset_position_rotation[0] = QVector3D(ptr_to_state_of_models->value(QString("square"))->get_x_offset(), ptr_to_state_of_models->value(QString("square"))->get_y_offset(), ptr_to_state_of_models->value(QString("square"))->get_z_offset());
			offset_position_rotation[1] = QVector3D(ptr_to_state_of_models->value(QString("square"))->get_x_rotation(), ptr_to_state_of_models->value(QString("square"))->get_y_rotation(), ptr_to_state_of_models->value(QString("square"))->get_z_rotation());
			offset_position_rotation[2] = QVector3D(ptr_to_state_of_models->value(QString("square"))->get_x_scale(), ptr_to_state_of_models->value(QString("square"))->get_y_scale(), ptr_to_state_of_models->value(QString("square"))->get_z_scale());
			
			color_shader_program->setUniformValueArray("offset_position_rotation", offset_position_rotation, 3);
			int square_do_write_vbo = ptr_to_state_of_models->value(QString("square"))->get_flag_vbo();
			if(square_do_write_vbo == 1)
			{
				//write
				square_ogl_vbo_quad->write(0, positions_and_colors, combined_tuple_size  * sizeof(GLfloat));
			}
			color_shader_program->enableAttributeArray(0);
			color_shader_program->enableAttributeArray(1);
		
			color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
			color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
			glDrawArrays(GL_TRIANGLES, 0, 6);
			square_ogl_vao_quad->release();
			square_ogl_vbo_quad->release();
			color_shader_program->release();
		}
		*/
		
		//triangle
		int	triangle_do_render = ptr_to_state_of_models->value(QString("triangle"))->get_flag_render_model();
		if(triangle_do_render == 1)
		{
			int triangle_do_write_vbo = ptr_to_state_of_models->value(QString("triangle"))->get_flag_vbo();
			if(triangle_do_write_vbo == 1)
			{
				color_shader_program->bind();
				triangle_ogl_vao_quad.bind();
				triangle_ogl_vbo_quad->bind();
				square_ogl_vbo_quad->setUsagePattern(QOpenGLBuffer::StaticDraw);
				
				//allocate or write
				int * array_of_index = 0; while(array_of_index == 0){ array_of_index = (int*)malloc(2*sizeof(GLfloat));}
				array_of_index[0] = 0;
				array_of_index[1] = 1;
				GLfloat * positions_and_colors = ptr_to_state_of_models->value(QString("triangle"))->get_combined_tuple(array_of_index);
				long int combined_tuple_size = ptr_to_state_of_models->value(QString("triangle"))->get_combined_size(array_of_index);
				free(array_of_index);
//qDebug() << "tuple sizs" << combined_tuple_size;
				if(init_triangle == 1)
				{
					triangle_ogl_vbo_quad->allocate(positions_and_colors, combined_tuple_size  * sizeof(GLfloat));
					ptr_to_state_of_models->value(QString("triangle"))->scale(0.5, 0.5, 0.5);
					ptr_to_state_of_models->value(QString("triangle"))->translate(0.5, 0.5, 0.5);
					init_triangle = 0;
				}
				
				QVector3D offset_position_rotation[3];
				offset_position_rotation[0] = QVector3D(ptr_to_state_of_models->value(QString("triangle"))->get_x_offset(), ptr_to_state_of_models->value(QString("triangle"))->get_y_offset(), ptr_to_state_of_models->value(QString("triangle"))->get_z_offset());
				offset_position_rotation[1] = QVector3D(ptr_to_state_of_models->value(QString("triangle"))->get_x_rotation(), ptr_to_state_of_models->value(QString("triangle"))->get_y_rotation(), ptr_to_state_of_models->value(QString("triangle"))->get_z_rotation());
				offset_position_rotation[2] = QVector3D(ptr_to_state_of_models->value(QString("triangle"))->get_x_scale(), ptr_to_state_of_models->value(QString("triangle"))->get_y_scale(), ptr_to_state_of_models->value(QString("triangle"))->get_z_scale());
				
				color_shader_program->setUniformValueArray("offset_position_rotation", offset_position_rotation, 3);
				
				//write
				triangle_ogl_vbo_quad->write(0, positions_and_colors, combined_tuple_size  * sizeof(GLfloat));
				
			
				color_shader_program->enableAttributeArray(0);
				color_shader_program->enableAttributeArray(1);
			
				color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
				color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
				glDrawArrays(GL_TRIANGLES, 0, 6);
				triangle_ogl_vao_quad.release();
				triangle_ogl_vbo_quad->release();
				color_shader_program->release();
			}
		}
		//update visual physical frame
		this->update();
	QTimer::singleShot((1000/60), this, SLOT(run_paint()));
	
}
