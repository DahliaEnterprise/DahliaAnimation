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
		
		load_shader->loadVertex(QString("./../DahliaAnimation/source/shader_vertex/texture.c"));
		load_shader->vertex_readAll();
		load_shader->addVertexShaderFromSourceCode();
		
		load_shader->loadFragment(QString("./../DahliaAnimation/source/shader_fragment/texture.c"));
		load_shader->fragment_readAll();
		load_shader->addFragmentShaderFromSourceCode();
		texture_shader_program = load_shader->get_shader_program();

		
		init_square = 1;
		
		//initialize square
		this->create_model_positions_and_colors("square", QString("./../DahliaAnimation/source/vertex/square.xyz") , QString("./../DahliaAnimation/source/vertex_color/square.rgb"));
		
		
		
		//triangle
		this->create_model_positions_and_texture_positions("triangle", QString("./../DahliaAnimation/source/vertex/triangle.xyz"), QString("./../DahliaAnimation/source/vertex_texture_position/triangle.texture_xy"), QString("./../DahliaAnimation/images/dev_test/diagnal.png"));
		/*	
		color_shader_program->bind();
			
			QOpenGLVertexArrayObject * triangle_ogl_vao_quad = new QOpenGLVertexArrayObject();
			triangle_ogl_vao_quad->create();
			triangle_ogl_vao_quad->bind();
			
			QOpenGLBuffer * triangle_ogl_vbo_quad = new QOpenGLBuffer();
			triangle_ogl_vbo_quad->create();
			triangle_ogl_vbo_quad->setUsagePattern(QOpenGLBuffer::StaticDraw);
			triangle_ogl_vbo_quad->bind();
			
			
			state_of_model * triangle_model_state_information = new state_of_model();
			triangle_model_state_information->initialize(2);
			triangle_model_state_information->load_vertex_positions(QString("./../DahliaAnimation/source/vertex/triangle.xyz"));
			triangle_model_state_information->load_vertex_texture_positions(QString("./../DahliaAnimation/source/vertex_texture_position/triangle.texture_xy"));
			list_of_models->insert("triangle", triangle_model_state_information);
			
			//associate vao and vbo.
			list_of_models->value(QString("triangle"))->associate_vao(triangle_ogl_vao_quad);
			list_of_models->value(QString("triangle"))->associate_vbo(triangle_ogl_vbo_quad);
			
			list_of_models->value(QString("triangle"))->set_texture_image(QImage("./../DahliaAnimation/images/dev_test/diagnal.png"));
			
			
			//clean/clear
			triangle_ogl_vao_quad->release();
			triangle_ogl_vbo_quad->release();
			color_shader_program->release();
			*/
		//starting values
		list_of_models->value("triangle")->scale(-0.9, -0.9, -0.9);
		list_of_models->value("square")->set_flag_render_model(1);
		
		list_of_models->value("triangle")->set_flag_render_model(1);
		list_of_models->value("triangle")->translate(-0.5, -0.5, 0.0);
		
		start_x = -0.5;
		end_x = 0.9;
		current_x = start_x;
		start_y = -0.5;
		end_y = 0.5;
		current_y = start_y;
		start_z = 0.0;
		end_z = 0.0;
		current_z = start_z;
	
		ballsize = 0.001;
		
		prestage = 0;
	}else if(prestage == 2)
	{
		
		
	}else if(prestage == 0)
	{
		float offset_x = 0.0;
		float offset_y = 0.0;
		float offset_z = 0.0;
		
		float x_distance = abs(start_x-end_x);
		float y_distance = abs(start_y-end_y);
		float z_distance = abs(start_z-end_z);
		//x distance is larger than y distance.
		float resolution = 1000000;
		float x_distance_per_one_resolution = x_distance / resolution;
		float y_distance_per_one_resolution = y_distance / resolution;
		float z_distance_per_one_resolution = z_distance / resolution;
	
		int longest_plane = -1;
		if((x_distance * 1000000) >= (y_distance * 1000000) && (x_distance * 1000000) >= (z_distance * 1000000))
		{
			longest_plane = 0;
		}else if((y_distance * 1000000) > (x_distance * 1000000) && (y_distance * 1000000) > (z_distance * 1000000))
		{
			longest_plane = 1;
		}else{
			longest_plane = 2;
		}
		
		if(longest_plane == 0)
		{
			//x is the longest distance.
			
		}
	}
}



void scene_one::render()
{
	
	QOpenGLVertexArrayObject * vao = list_of_models->value("square")->get_vao();
	QOpenGLBuffer * vbo = list_of_models->value("square")->get_vbo();
	draw_arrays_using_color_shader((char*)"square", vao, vbo, 6);
	

	
	vao = list_of_models->value("triangle")->get_vao();
	vbo = list_of_models->value("triangle")->get_vbo();
	//draw_arrays_using_texture_shader((char*)"square", vao, vbo, 6);
	
	
	texture_shader_program->bind();
	vao->bind();
	vbo->bind();
	vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
		
	int * array_of_index = 0; while(array_of_index == 0){ array_of_index = (int*)malloc(2*sizeof(GLfloat));} array_of_index[0] = 0; array_of_index[1] = 1;
	int * array_of_vector_size = 0; while(array_of_vector_size == 0){ array_of_vector_size = (int*)malloc(2*sizeof(GLfloat));} array_of_vector_size[0] = 3; array_of_vector_size[1] = 2;
	GLfloat * positions_and_texture_coordinates = list_of_models->value(QString("triangle"))->get_combined_tuple(array_of_index, array_of_vector_size);
	long int combined_tuple_size = list_of_models->value(QString("triangle"))->get_combined_size(array_of_index);
	free(array_of_index);

	/*QVector3D offset_position_rotation[3];
	offset_position_rotation[0] = QVector3D(0.0, 0.0, 0.0); //QVector3D(list_of_models->value(QString(model_name))->get_x_offset(), list_of_models->value(QString(model_name))->get_y_offset(), list_of_models->value(QString(model_name))->get_z_offset());
	offset_position_rotation[1] = QVector3D(0.0, 0.0, 0.0); //QVector3D(list_of_models->value(QString(model_name))->get_x_rotation(), list_of_models->value(QString(model_name))->get_y_rotation(), list_of_models->value(QString(model_name))->get_z_rotation());
	offset_position_rotation[2] = QVector3D(0.0, 0.0, 0.0); //QVector3D(list_of_models->value(QString(model_name))->get_x_scale(), list_of_models->value(QString(model_name))->get_y_scale(), list_of_models->value(QString(model_name))->get_z_scale());
	*/
		
	vbo->allocate(positions_and_texture_coordinates, combined_tuple_size  * sizeof(GLfloat));
	
	//texture_shader_program->setUniformValueArray("offset_position_rotation", offset_position_rotation, 3);
	texture_shader_program->setUniformValue("texture", 0);
	texture_shader_program->enableAttributeArray(0);
	texture_shader_program->enableAttributeArray(1);
	glActiveTexture(0);
	texture_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 5*sizeof(GLfloat));
	texture_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 2, 5*sizeof(GLfloat));
	
	list_of_models->value("triangle")->get_texture()->bind();
	
	glDrawArrays(GL_TRIANGLES, 0, 3);
	vao->release();
	vbo->release();
	texture_shader_program->release();

	//draw_arrays_using_color_shader((char*)"triangle", vao, vbo, 3);
	
	
}

void scene_one::create_model_positions_and_colors(char * model_name, QString positions_file_location, QString colors_file_location)
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

void scene_one::create_model_positions_and_texture_positions(char * model_name, QString positions_file_location, QString texture_positions_file_location, QString texture_image_file_location)
{
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

void scene_one::draw_arrays_using_texture_shader(char * model_name, QOpenGLVertexArrayObject * vao, QOpenGLBuffer * vbo, int total_points_of_triangles)
{
	int	do_render = list_of_models->value(QString(model_name))->get_flag_render_model();
	if(do_render == 1)
	{
		
	}
}


