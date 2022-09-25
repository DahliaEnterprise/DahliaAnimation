QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In orDEFINESder to do so, uncomment the following line.
# += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    opengl_manager.cpp \
    openglwindows.cpp \
    state_machine/controller/three_triangles/controller_three_triangles.cpp \
    state_machine/meta_model/meta_model.cpp \
    state_machine/scene/scene_one/scene_one.cpp \
    state_machine/scene_tool/load_and_compile_shader/load_and_compile_shader.cpp \
    state_machine/state_of_model/state_of_model.cpp \
    state_machine/tuple_float/tuple_float.cpp \
    tool/meta_model_viewer/meta_model_viewer.cpp \
    tool/model_viewer/model_viewer.cpp \
    vertex_group.cpp

HEADERS += \
    opengl_manager.h \
    openglwindows.h \
    state_machine/controller/three_triangles/controller_three_triangles.h \
    state_machine/meta_model/meta_model.h \
    state_machine/scene/scene_one/scene_one.h \
    state_machine/scene_tool/load_and_compile_shader/load_and_compile_shader.h \
    state_machine/state_of_model/state_of_model.h \
    state_machine/tuple_float/tuple_float.h \
    tool/meta_model_viewer/meta_model_viewer.h \
    tool/model_viewer/model_viewer.h \
    vertex_group.h



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
