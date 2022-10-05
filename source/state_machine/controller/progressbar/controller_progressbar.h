#ifndef CONTROLLER_PROGRESSBAR_H
#define CONTROLLER_PROGRESSBAR_H

#include <QObject>
#include <QMap>
#include <QString>

#include "./state_machine/state_of_model/state_of_model.h"
#include "./state_machine/scene_tool/load_and_compile_shader/load_and_compile_shader.h"


class controller_progressbar : public QObject
{
    Q_OBJECT
public:
    explicit controller_progressbar(QObject *parent = nullptr);

		void initialize(QMap<QString, state_of_model *> * set_list_of_models, load_and_compile_shader * set_load_and_compile_shader);
		void iterate();
		
private:
		QMap<QString, state_of_model *> * ptr_to_list_of_models;
		load_and_compile_shader * ptr_to_load_and_compile_shader;
		
		
		int stage;
		
		long long int total_bytes_loaded;
		long long int total_bytes_to_load;
		
signals:

};

#endif // CONTROLLER_PROGRESSBAR_H
