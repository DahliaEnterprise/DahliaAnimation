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
		
		load_shader = new load_and_compile_shader();
		load_shader->loadVertex(QString("./../DahliaAnimation/source/shader_vertex/color_triangles_test_point_within_vertex.c"));
		load_shader->vertex_readAll();
		load_shader->addVertexShaderFromSourceCode();
		
		load_shader->loadFragment(QString("./../DahliaAnimation/source/shader_fragment/color_triangles_test_point_within_vertex_fragment.c"));
		load_shader->fragment_readAll();
		load_shader->addFragmentShaderFromSourceCode();
		
		color_shader_program = load_shader->get_shader_program();
		
		load_shader->loadVertex(QString("./../DahliaAnimation/source/shader_vertex/lines_white.c"));
		load_shader->vertex_readAll();
		load_shader->addVertexShaderFromSourceCode();
		
		load_shader->loadFragment(QString("./../DahliaAnimation/source/shader_fragment/lines_white.c"));
		load_shader->fragment_readAll();
		load_shader->addFragmentShaderFromSourceCode();
		line_shader_program = load_shader->get_shader_program();
		
		
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
	}else if(prestage == 2)
	{
		
	}else if(prestage == 0)
	{
	
	  if(flash_square == 0)
		{
			flash_square = 1;
			
		}else{
			flash_square = 0;
			
		}
	
		list_of_models->value("square")->set_flag_render_model(1);
		
		list_of_models->value("triangle")->set_flag_render_model(1);
	}
}



void scene_one::associate_color_shader(QOpenGLShaderProgram * set_color_shader_program)
{
	color_shader_program = set_color_shader_program;
}



void scene_one::render()
{
	
	QOpenGLVertexArrayObject * vao = list_of_models->value("square")->get_vao();
	QOpenGLBuffer * vbo = list_of_models->value("square")->get_vbo();
	draw_arrays_using_color_shader((char*)"square", vao, vbo, 6);
	

	
	vao = list_of_models->value("triangle")->get_vao();
	vbo = list_of_models->value("triangle")->get_vbo();
	draw_arrays_using_color_shader((char*)"triangle", vao, vbo, 3);
	
	
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
		
		int * array_of_index = 0; while(array_of_index == 0){ array_of_index = (int*)malloc(2*sizeof(GLfloat));} array_of_index[0] = 0; array_of_index[1] = 1;
	GLfloat * positions_and_colors = list_of_models->value(QString(model_name))->get_combined_tuple(array_of_index);
	long int combined_tuple_size = list_of_models->value(QString(model_name))->get_combined_size(array_of_index);
	free(array_of_index);
	
	QVector3D offset_position_rotation[3];
	offset_position_rotation[0] = QVector3D(list_of_models->value(QString(model_name))->get_x_offset(), list_of_models->value(QString(model_name))->get_y_offset(), list_of_models->value(QString(model_name))->get_z_offset());
	offset_position_rotation[1] = QVector3D(list_of_models->value(QString(model_name))->get_x_rotation(), list_of_models->value(QString(model_name))->get_y_rotation(), list_of_models->value(QString(model_name))->get_z_rotation());
	offset_position_rotation[2] = QVector3D(list_of_models->value(QString(model_name))->get_x_scale(), list_of_models->value(QString(model_name))->get_y_scale(), list_of_models->value(QString(model_name))->get_z_scale());
	
		
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
	}
}


