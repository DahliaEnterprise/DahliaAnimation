#include "scene_one.h"

scene_one::scene_one(QObject *parent)
    : QObject{parent}
{
	prestage = 1;
	
	list_of_models = new QMap<QString, state_of_model *>();
	
	
}


void scene_one::iterate()
{
	
	if(prestage == 1)
	{
		//MUTED: tool_model_viewer = new model_viewer();
		
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
		
		load_shader->loadVertex(QString("./../DahliaAnimation/source/shader_vertex/texture.c"));
		load_shader->vertex_readAll();
		load_shader->addVertexShaderFromSourceCode();
		
		load_shader->loadFragment(QString("./../DahliaAnimation/source/shader_fragment/texture.c"));
		load_shader->fragment_readAll();
		load_shader->addFragmentShaderFromSourceCode();
		texture_shader_program = load_shader->get_shader_program();
		
		//square
		this->create_model_positions_and_colors(QString("square"), QString("./../DahliaAnimation/source/vertex/square.xyz") , QString("./../DahliaAnimation/source/vertex_color/square.rgb"));
		
		//triangle
		this->create_model_positions_and_colors(QString("triangle_one"), QString("./../DahliaAnimation/source/vertex/triangle.xyz"), QString("./../DahliaAnimation/source/vertex_color/triangle.rgb"));
		this->create_model_positions_and_colors(QString("triangle_two"), QString("./../DahliaAnimation/source/vertex/triangle.xyz"), QString("./../DahliaAnimation/source/vertex_color/triangle.rgb"));
		this->create_model_positions_and_colors(QString("triangle_three"), QString("./../DahliaAnimation/source/vertex/triangle.xyz"), QString("./../DahliaAnimation/source/vertex_color/triangle.rgb"));
		
		//controllers
		controller_of_three_triangles = new controller_three_triangles();
		controller_of_three_triangles->initialize(list_of_models);
		
		list_of_models->value("square")->set_flag_render_model(1);
		
		//to be replaced by respective controllers.
		//starting values
	
		/*list_of_models->value("triangle")->scale(-0.9, -0.9, -0.9);
		list_of_models->value("square")->set_flag_render_model(1);
		
		list_of_models->value("triangle")->set_flag_render_model(1);
		list_of_models->value("triangle")->translate(-0.5, -0.5, 0.0);
		*/
		
		prestage = 0;
	}else if(prestage == 2)
	{
		
		
	}else if(prestage == 0)
	{
		controller_of_three_triangles->iterate();
	}
}



void scene_one::render()
{
	
	QOpenGLVertexArrayObject * vao = list_of_models->value("square")->get_vao();
	QOpenGLBuffer * vbo = list_of_models->value("square")->get_vbo();
	draw_arrays_using_color_shader(QString("square"), vao, vbo, 6);
	
	vao = list_of_models->value("triangle_one")->get_vao();
	vbo = list_of_models->value("triangle_one")->get_vbo();
	draw_arrays_using_color_shader(QString("triangle_one"), vao, vbo, 3);
	
	vao = list_of_models->value("triangle_two")->get_vao();
	vbo = list_of_models->value("triangle_two")->get_vbo();
	draw_arrays_using_color_shader(QString("triangle_two"), vao, vbo, 3);
	
	
	vao = list_of_models->value("triangle_three")->get_vao();
	vbo = list_of_models->value("triangle_three")->get_vbo();
	draw_arrays_using_color_shader(QString("triangle_three"), vao, vbo, 3);
	
}

/*******
			Render triangles (variety of render methods)
********/

void scene_one::create_model_positions_and_colors(QString model_name, QString positions_file_location, QString colors_file_location)
{
	QOpenGLVertexArrayObject * vao = new QOpenGLVertexArrayObject();
	vao->create();
	vao->bind();
	
	QOpenGLBuffer * vbo = new QOpenGLBuffer();
	vbo->create();
	vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
	vbo->bind();
	
	state_of_model * model_state_information = new state_of_model();
	model_state_information->initialize(2);
	model_state_information->load_vertex_positions(positions_file_location);
	model_state_information->load_vertex_colors(colors_file_location);
	list_of_models->insert(model_name, model_state_information);
	
	//associate vao and vbo.
	list_of_models->value(QString(model_name))->associate_vao(vao);
	list_of_models->value(QString(model_name))->associate_vbo(vbo);
	
	//clean/clear
	vao->release();
	vbo->release();
}

void scene_one::create_model_positions_and_texture_positions(QString model_name, QString positions_file_location, QString texture_positions_file_location, QString texture_image_file_location)
{
	texture_shader_program->bind();
	QOpenGLVertexArrayObject * triangle_ogl_vao_quad = new QOpenGLVertexArrayObject();
		triangle_ogl_vao_quad->create();
		triangle_ogl_vao_quad->bind();
		
		QOpenGLBuffer * triangle_ogl_vbo_quad = new QOpenGLBuffer();
		triangle_ogl_vbo_quad->create();
		triangle_ogl_vbo_quad->setUsagePattern(QOpenGLBuffer::StaticDraw);
		triangle_ogl_vbo_quad->bind();
		
		
		state_of_model * triangle_model_state_information = new state_of_model();
		triangle_model_state_information->initialize(2);
		triangle_model_state_information->load_vertex_positions(positions_file_location);
		triangle_model_state_information->load_vertex_texture_positions(texture_positions_file_location);
		list_of_models->insert(model_name, triangle_model_state_information);
		
		//associate vao and vbo.
		list_of_models->value(QString(model_name))->associate_vao(triangle_ogl_vao_quad);
		list_of_models->value(QString(model_name))->associate_vbo(triangle_ogl_vbo_quad);
		
		list_of_models->value(QString(model_name))->set_texture_image(QImage(texture_image_file_location));
		
		
		//clean/clear
		triangle_ogl_vao_quad->release();
		triangle_ogl_vbo_quad->release();
}

void scene_one::draw_arrays_using_color_shader(QString model_name, QOpenGLVertexArrayObject * vao, QOpenGLBuffer * vbo, int total_points_of_triangles)
{
	int	do_render = list_of_models->value(model_name)->get_flag_render_model();
	if(do_render == 1)
	{
		color_shader_program->bind();
		vao->bind();
		vbo->bind();
		vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
		
		int * array_of_index = 0; while(array_of_index == 0){ array_of_index = (int*)malloc(2*sizeof(GLfloat));} array_of_index[0] = 0; array_of_index[1] = 1;
		int * array_of_vector_size = 0; while(array_of_vector_size == 0){ array_of_vector_size = (int*)malloc(2*sizeof(GLfloat));} array_of_vector_size[0] = 3; array_of_vector_size[1] = 3;
		GLfloat * positions_and_colors = list_of_models->value(QString(model_name))->get_combined_tuple(array_of_index, array_of_vector_size);
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

void scene_one::draw_arrays_using_texture_shader(QString model_name, QOpenGLVertexArrayObject * vao, QOpenGLBuffer * vbo, int total_points_of_triangles)
{
	int	do_render = list_of_models->value(model_name)->get_flag_render_model();
	do_render = 1;
	if(do_render == 1)
	{
		texture_shader_program->bind();
		list_of_models->value(model_name)->get_texture()->bind();
		glActiveTexture(0);
		
		vao->bind();
		vbo->bind();
		vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
			
		int * array_of_index = 0; while(array_of_index == 0){ array_of_index = (int*)malloc(2*sizeof(GLfloat));} array_of_index[0] = 0; array_of_index[1] = 1;
		int * array_of_vector_size = 0; while(array_of_vector_size == 0){ array_of_vector_size = (int*)malloc(2*sizeof(GLfloat));} array_of_vector_size[0] = 3; array_of_vector_size[1] = 2;
		GLfloat * positions_and_texture_coordinates = list_of_models->value(QString(model_name))->get_combined_tuple(array_of_index, array_of_vector_size);
		long int combined_tuple_size = list_of_models->value(QString(model_name))->get_combined_size(array_of_index);
		free(array_of_index);
	
		QVector3D offset_position_rotation[3];
		offset_position_rotation[0] = QVector3D(list_of_models->value(QString(model_name))->get_x_offset(), list_of_models->value(QString(model_name))->get_y_offset(), list_of_models->value(QString(model_name))->get_z_offset());
		offset_position_rotation[1] = QVector3D(list_of_models->value(QString(model_name))->get_x_rotation(), list_of_models->value(QString(model_name))->get_y_rotation(), list_of_models->value(QString(model_name))->get_z_rotation());
		offset_position_rotation[2] = QVector3D(list_of_models->value(QString(model_name))->get_x_scale(), list_of_models->value(QString(model_name))->get_y_scale(), list_of_models->value(QString(model_name))->get_z_scale());
		
			
		vbo->allocate(positions_and_texture_coordinates, combined_tuple_size  * sizeof(GLfloat));
		
		texture_shader_program->setUniformValueArray("offset_position_rotation", offset_position_rotation, 3);
		texture_shader_program->setUniformValue("texture_slot", 0);
		texture_shader_program->enableAttributeArray(0);
		texture_shader_program->enableAttributeArray(1);
		
		texture_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 5*sizeof(GLfloat));
		texture_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 2, 5*sizeof(GLfloat));
		
		
		glDrawArrays(GL_TRIANGLES, 0, total_points_of_triangles);
		vao->release();
		vbo->release();
		texture_shader_program->release();
		
	}
}


