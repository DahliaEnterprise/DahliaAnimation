#include "openglwindows.h"

openglwindows::openglwindows()
{

}

const char* vertexSource =
        "#version 330\n"
        "layout(location = 0) in vec3 position;\n"
        "layout(location = 1) in vec3 incolor;\n"
        "out vec4 color;\n"
				"out vec4 vertex_position;\n"
        "void main( void )\n"
        "{\n"
        " gl_Position = vec4(position, 1.0);\n"
        " color = vec4(incolor, 1.0);\n"
				" vertex_position = vec4(position, 1.0);\n"
        "}\n";

const char* fragmentSource =
        "#version 330\n"
        "in vec4 color;\n"
				"in vec4 vertex_position;\n"
				"float light_intensity_factor(in float light_source_distance)\n"
				"{\n"
				"	float result = 0.0;\n"
				"	if((light_source_distance * 1000000) < (1.0 * 1000000))\n"
				"	{\n"
				"		result = 1.0 - ((light_source_distance)+(light_source_distance * 0.5));\n"
			  "	}else if((light_source_distance * 1000000) >= (1.0 * 1000000)){\n"
				"		float initial_intensity = 0.0;\n"
				"		result = 0;\n"
				"	}\n"
				"	return result;\n"
				"}\n"
				
        "void main( void )\n"
        "{\n"
				"vec4 nolight_color = vec4(0.0, 0.0, 0.0, 1.0);\n"
				"vec3 light_position = vec3(0.0, 0.5, 0.0);\n"
				"float light_distance = distance(vertex_position, vec4(light_position, 1.0));\n"
				"float light_intensity = light_intensity_factor(light_distance);\n"
				"vec4 mixed_color = mix(nolight_color, color, light_intensity);\n"
        " gl_FragColor = mixed_color; \n"
        "}\n";
				
vertex_group * triangle_vertex_and_colors_unaltered;
vertex_group * triangle_vertex_and_colors_altered;
vertex_group * triangle_vertex_and_colors_texture_coordinates;


vertex_group * triangle_two_vertex_and_colors_unaltered;

rotate_2d * rotate;

void openglwindows::initializeGL()
{
	triangle_vertex_and_colors_unaltered = new vertex_group();
	triangle_vertex_and_colors_unaltered->setPositions(QUrl("./../DahliaAnimation/source/vertex/triangle.xyz"));
	triangle_vertex_and_colors_unaltered->setColors(QUrl("./../DahliaAnimation/source/vertex_color/triangle.rgb"));
	triangle_vertex_and_colors_unaltered->combined_xyz_colors();
	
	triangle_vertex_and_colors_altered = new vertex_group();
	triangle_vertex_and_colors_altered->setCombinedXyzColors(triangle_vertex_and_colors_unaltered->combined_xyz_colors(), triangle_vertex_and_colors_unaltered->combined_total_xyz_colors());
	triangle_vertex_and_colors_altered->combined_xyz_colors();
	
	triangle_vertex_and_colors_texture_coordinates = new vertex_group();
	triangle_vertex_and_colors_texture_coordinates->setTexturePositions(QUrl("./../DahliaAnimation/source/vertex_texture_position/triangle.texture_xy"));
	
	triangle_two_vertex_and_colors_unaltered = new vertex_group();
	triangle_two_vertex_and_colors_unaltered->setPositions(QUrl("./../DahliaAnimation/source/vertex/triangle-1.xyz"));
	triangle_two_vertex_and_colors_unaltered->setColors(QUrl("./../DahliaAnimation/source/vertex_color/triangle.rgb"));
	triangle_two_vertex_and_colors_unaltered->combined_xyz_colors();
	
	
	rotate = new rotate_2d();
	
  initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 1.0f, 0.9f);
	qDebug() << "initializing";
	color_shader_program = new QOpenGLShaderProgram();
	bool success = color_shader_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexSource);
	if(!success) {
		qDebug() << "vertex";
	}

	success = color_shader_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentSource);
	if(!success) {
		qDebug() << "fragment";
	}
	
	color_shader_program->bindAttributeLocation("position", 0);
	color_shader_program->link();
	color_shader_program->bind();
		
	triangle_ogl_vao_quad.create();
	triangle_ogl_vao_quad.bind();
	
	triangle_ogl_vbo_quad = new QOpenGLBuffer();
	triangle_ogl_vbo_quad->create();
	triangle_ogl_vbo_quad->setUsagePattern(QOpenGLBuffer::StaticDraw);
	triangle_ogl_vbo_quad->bind();

	
	triangle_ogl_vbo_quad->allocate(triangle_vertex_and_colors_altered->combined_xyz_colors(), triangle_vertex_and_colors_altered->combined_total_xyz_colors() * sizeof(GLfloat));
		
	color_shader_program->enableAttributeArray(0);
	color_shader_program->enableAttributeArray(1);
	color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
	color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
		
	//clean/clear
	triangle_ogl_vao_quad.release();
	triangle_ogl_vbo_quad->release();
	color_shader_program->release();
	
	color_shader_program->bind();
		
	triangle_two_ogl_vao_quad.create();
	triangle_two_ogl_vao_quad.bind();
	
	triangle_two_ogl_vbo_quad = new QOpenGLBuffer();
	triangle_two_ogl_vbo_quad->create();
	triangle_two_ogl_vbo_quad->setUsagePattern(QOpenGLBuffer::StaticDraw);
	triangle_two_ogl_vbo_quad->bind();
	triangle_two_ogl_vbo_quad->allocate(triangle_two_vertex_and_colors_unaltered->combined_xyz_colors(), triangle_two_vertex_and_colors_unaltered->combined_total_xyz_colors() * sizeof(GLfloat));
		
	color_shader_program->enableAttributeArray(0);
	color_shader_program->enableAttributeArray(1);
	color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
	color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
		
	//clean/clear
	triangle_two_ogl_vao_quad.release();
	triangle_two_ogl_vbo_quad->release();
	color_shader_program->release();
		qDebug() << "run";
		QTimer::singleShot(200, this, SLOT(run_paint()));
		
}
 
void openglwindows::resizeGL(int width, int height)
{
  (void)width;
  (void)height;
}
 GLfloat rotation = 0.01;
void openglwindows::paintGL()
{
	
	}
 
void openglwindows::run_paint()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	
    color_shader_program->bind();
    triangle_ogl_vao_quad.bind();
		triangle_ogl_vbo_quad->bind();
		triangle_vertex_and_colors_altered->setCombinedXyzColors(	rotate->rotate_z(triangle_vertex_and_colors_altered->combined_xyz_colors(), triangle_vertex_and_colors_altered->combined_total_xyz_colors(), rotation), triangle_vertex_and_colors_altered->combined_total_xyz_colors());
    triangle_ogl_vbo_quad->allocate(triangle_vertex_and_colors_altered->combined_xyz_colors(), triangle_vertex_and_colors_altered->combined_total_xyz_colors() * sizeof(GLfloat));
		color_shader_program->enableAttributeArray(0);
		color_shader_program->enableAttributeArray(1);
		color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
		color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
		
		triangle_ogl_vbo_quad->release();
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		triangle_ogl_vao_quad.release();
		
		/*triangle_two_ogl_vao_quad.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
		triangle_two_ogl_vao_quad.release();*/
		
		
		color_shader_program->release();
		this->update();
	QTimer::singleShot((1000/60), this, SLOT(run_paint()));
	
}

