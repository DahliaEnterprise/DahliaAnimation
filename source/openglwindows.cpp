#include "openglwindows.h"

openglwindows::openglwindows()
{

}

const char* vertexSource =
        "#version 330\n"
        "layout(location = 0) in vec3 position;\n"
        "layout(location = 1) in vec3 incolor;\n"
        "out vec4 color;\n"
        "void main( void )\n"
        "{\n"
        " gl_Position = vec4(position, 1.0);\n"
        " color = vec4(incolor, 1.0);\n"
        "}\n";

const char* fragmentSource =
        "#version 330\n"
        "in vec4 color;\n"
        "out vec4 outColor;\n"
        "void main( void )\n"
        "{\n"
        " outColor = color;\n"
        "}\n";
				
vertex_group * triangle_vertex_and_colors_unaltered;
vertex_group * triangle_vertex_and_colors_altered;

vertex_group * triangle_two_vertex_and_colors_unaltered;

rotate_2d * rotate;

void openglwindows::initializeGL()
{
	triangle_vertex_and_colors_unaltered = new vertex_group();
	triangle_vertex_and_colors_unaltered->setPositions(QUrl("./../dahliaanimator/vertex/triangle.xyz"));
	triangle_vertex_and_colors_unaltered->setColors(QUrl("./../dahliaanimator/vertex_color/triangle.rgb"));
	triangle_vertex_and_colors_unaltered->combined_xyz_colors();
	
	triangle_vertex_and_colors_altered = new vertex_group();
	triangle_vertex_and_colors_altered->setCombinedXyzColors(triangle_vertex_and_colors_unaltered->combined_xyz_colors(), triangle_vertex_and_colors_unaltered->combined_total_xyz_colors());
	triangle_vertex_and_colors_altered->combined_xyz_colors();
	
	triangle_two_vertex_and_colors_unaltered = new vertex_group();
	triangle_two_vertex_and_colors_unaltered->setPositions(QUrl("./../dahliaanimator/vertex/triangle-1.xyz"));
	triangle_two_vertex_and_colors_unaltered->setColors(QUrl("./../dahliaanimator/vertex_color/triangle.rgb"));
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
	rotate->rotate_z(triangle_vertex_and_colors_altered->combined_xyz_colors(), triangle_vertex_and_colors_altered->combined_total_xyz_colors(), (GLfloat)1.34);
	
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
	
}
 
void openglwindows::resizeGL(int width, int height)
{
  (void)width;
  (void)height;
}
 
void openglwindows::paintGL()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    color_shader_program->bind();
    triangle_ogl_vao_quad.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
		triangle_ogl_vao_quad.release();
		
		triangle_two_ogl_vao_quad.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
		triangle_two_ogl_vao_quad.release();
		
		color_shader_program->release();
}
 

