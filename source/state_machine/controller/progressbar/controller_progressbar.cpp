#include "controller_progressbar.h"

controller_progressbar::controller_progressbar(QObject *parent)
    : QObject{parent}
{

}

void controller_progressbar::initialize(QMap<QString, state_of_model *> * set_list_of_models, load_and_compile_shader * set_load_and_compile_shader)
{
	ptr_to_list_of_models = set_list_of_models;
	ptr_to_load_and_compile_shader = set_load_and_compile_shader;
	
	
	ptr_to_list_of_models->value("progressbar_square")->scale(-0.999999, -0.5, 0.0);
	ptr_to_list_of_models->value("progressbar_square")->translate(0.0, 0.0, -0.1);
	
	stage = 1;
	
	total_bytes_loaded = 0;
	total_bytes_to_load = 0;
}

void controller_progressbar::iterate()
{
	if(stage == 1)
	{
		//determine total bytes to load
		total_bytes_to_load += ptr_to_load_and_compile_shader->get_total_bytes_of_shader_file(QString("./../DahliaAnimation/source/shader_sourcecode/shader_vertex/lines_white.c"));
		total_bytes_to_load += ptr_to_load_and_compile_shader->get_total_bytes_of_shader_file(QString("./../DahliaAnimation/source/shader_sourcecode/shader_fragment/lines_white.c"));
		total_bytes_to_load += ptr_to_load_and_compile_shader->get_total_bytes_of_shader_file(QString("./../DahliaAnimation/source/shader_sourcecode/shader_vertex/texture.c"));
		total_bytes_to_load += ptr_to_load_and_compile_shader->get_total_bytes_of_shader_file(QString("./../DahliaAnimation/source/shader_sourcecode/shader_fragment/texture.c"));
		
	
		stage = 2;
	}else if(stage == 2)
	{
		ptr_to_load_and_compile_shader->loadVertex(QString("./../DahliaAnimation/source/shader_sourcecode/shader_vertex/lines_white.c"));
		
		stage = 3;
	}else if(stage == 3)
	{
		long long int amount_read = ptr_to_load_and_compile_shader->vertex_read(1024);
		total_bytes_loaded += amount_read;
		
		float percentage_completed = (float)total_bytes_loaded / (float)total_bytes_to_load;
		float current_x_scale = ptr_to_list_of_models->value("progressbar_square")->get_x_scale();
		if((current_x_scale * 1000000) < (percentage_completed * 1000000))
		{
			float new_x_scale = current_x_scale + 0.001;
			ptr_to_list_of_models->value("progressbar_square")->set_x_scale(new_x_scale);
		}else if((current_x_scale * 1000000) >= (percentage_completed * 1000000))
		{
			ptr_to_list_of_models->value("progressbar_square")->set_x_scale(percentage_completed);
			if(amount_read == 0)
			{
				stage = 4;
			}
		}
	}else if(stage == 4)
	{
		ptr_to_load_and_compile_shader->loadVertex(QString("./../DahliaAnimation/source/shader_sourcecode/shader_fragment/lines_white.c"));
		
		stage = 5;
	}else if(stage == 5)
	{
		long long int amount_read = ptr_to_load_and_compile_shader->vertex_read(1024);
		total_bytes_loaded += amount_read;
		
		float percentage_completed = (float)total_bytes_loaded / (float)total_bytes_to_load;
		float current_x_scale = ptr_to_list_of_models->value("progressbar_square")->get_x_scale();
		if((current_x_scale * 1000000) < (percentage_completed * 1000000))
		{
			float new_x_scale = current_x_scale + 0.001;
			ptr_to_list_of_models->value("progressbar_square")->set_x_scale(new_x_scale);
		}else if((current_x_scale * 1000000) >= (percentage_completed * 1000000))
		{
			ptr_to_list_of_models->value("progressbar_square")->set_x_scale(percentage_completed);
			if(amount_read == 0)
			{
				stage = 6;
			}
		}
	}else if(stage == 6)
	{
		ptr_to_load_and_compile_shader->loadVertex(QString("./../DahliaAnimation/source/shader_sourcecode/shader_vertex/texture.c"));
		
		stage = 7;
	}else if(stage == 7)
	{
		long long int amount_read = ptr_to_load_and_compile_shader->vertex_read(1024);
		total_bytes_loaded += amount_read;
		
		float percentage_completed = (float)total_bytes_loaded / (float)total_bytes_to_load;
		float current_x_scale = ptr_to_list_of_models->value("progressbar_square")->get_x_scale();
		if((current_x_scale * 1000000) < (percentage_completed * 1000000))
		{
			float new_x_scale = current_x_scale + 0.001;
			ptr_to_list_of_models->value("progressbar_square")->set_x_scale(new_x_scale);
		}else if((current_x_scale * 1000000) >= (percentage_completed * 1000000))
		{
			ptr_to_list_of_models->value("progressbar_square")->set_x_scale(percentage_completed);
			if(amount_read == 0)
			{
				stage = 8;
			}
		}
	}
	
}