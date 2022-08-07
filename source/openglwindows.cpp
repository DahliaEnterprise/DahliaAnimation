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
        " outColor = vec4(1.0, 0.5, 0.0, 1.0); //color;\n"
        "}\n";
				
GLfloat * vertexData;
GLfloat * vertexData_two;

void openglwindows::initializeGL()
{
	triangle_vg = new vertex_group();
	triangle_vg->setPositions(QUrl("./../dahliaanimator/vertex/triangle.xyz"));
	triangle_vg->setColors(QUrl("./../dahliaanimator/vertex_color/triangle.rgb"));

	
	vertexData = 0;
	while(vertexData == 0){ vertexData = (GLfloat*)malloc(18*sizeof(GLfloat)); }
	
	vertexData[0] = 0.0;
	vertexData[1] = 0.5;
	vertexData[2] =-0.01;
	
	vertexData[3] = 1.0;
	vertexData[4] = 0.5;
	vertexData[5] = 0.0;
	
	//
	vertexData[6] = 0.5;
	vertexData[7] = -0.5;
	vertexData[8] = -0.01;
	
	vertexData[9] = 0.0;
	vertexData[10] = 1.0;
	vertexData[11] = 0.0;
	
	//
	vertexData[12] = -0.5;
	vertexData[13] = -0.5;
	vertexData[14] = -0.01;
	
	vertexData[15] = 0.0;
	vertexData[16] = 0.0;
	vertexData[17] = 1.0;
	
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
	triangle_ogl_vbo_quad->allocate(vertexData, 18 * sizeof(GLfloat));
		
	color_shader_program->enableAttributeArray(0);
	color_shader_program->enableAttributeArray(1);
	color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
	color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
		
	//clean/clear
	triangle_ogl_vao_quad.release();
	triangle_ogl_vbo_quad->release();
	color_shader_program->release();
	/*//
	color_shader_program->bind();
	
	triangle_two_ogl_vao_quad.create();
	triangle_two_ogl_vao_quad.bind();
	
	triangle_two_ogl_vbo_quad = new QOpenGLBuffer();
	triangle_two_ogl_vbo_quad->create();
	triangle_two_ogl_vbo_quad->setUsagePattern(QOpenGLBuffer::StaticDraw);
	triangle_two_ogl_vbo_quad->bind();
	triangle_two_ogl_vbo_quad->allocate(vertexData_two, 18 * sizeof(GLfloat));
	color_shader_program->enableAttributeArray(0);
	color_shader_program->enableAttributeArray(1);
	color_shader_program->setAttributeBuffer(0, GL_FLOAT, 0, 3, 6*sizeof(GLfloat));
	color_shader_program->setAttributeBuffer(1, GL_FLOAT, 3*sizeof(GLfloat), 3, 6*sizeof(GLfloat));
	*/
	
	
}
 
void openglwindows::resizeGL(int width, int height)
{
  (void)width;
  (void)height;
}
 
void openglwindows::paintGL()
{
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0, 1.0);
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
glClearDepth(1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    color_shader_program->bind();
	/*	triangle_two_ogl_vao_quad.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
		triangle_two_ogl_vao_quad.release();
		*/
	
		
		triangle_ogl_vao_quad.bind();
		triangle_ogl_vbo_quad->bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
		triangle_ogl_vao_quad.release();
		triangle_ogl_vbo_quad->release();
		color_shader_program->release();
}
 

