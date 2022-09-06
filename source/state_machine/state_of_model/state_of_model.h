#ifndef STATE_OF_MODEL_H
#define STATE_OF_MODEL_H

#include <QObject>

#include "vertex_group.h"

class state_of_model : public QObject
{
    Q_OBJECT
public:
    explicit state_of_model(QObject *parent = nullptr);

		void initialize();
		
		//set/get render options
		void set_flag_allocate();
		void set_flag_render_model(int do_render_flag);
		int get_flag_render_model();
		
		void load_vertex_positions(QString vertex_positions_filelocation);
		void load_vertex_colors(QString vertex_colors_filelocation);
		vertex_group * get_vertex_group();
		
		
	private:
		int flag_render_model;
		int flag_allocate_vbo;
		
		vertex_group * vertex_and_secondary;
		
		
signals:

};

#endif // STATE_OF_MODEL_H
