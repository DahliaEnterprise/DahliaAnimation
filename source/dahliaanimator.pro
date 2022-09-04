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
    rotation_scale_translate/rotation/rotate_2d.cpp \
    rotation_scale_translate/translate/translate.cpp \
    state_machine/game/game.cpp \
    state_machine/models/models.cpp \
    state_machine/state_machine.cpp \
    state_machine/state_of_model/state_of_model.cpp \
    vertex_group.cpp

HEADERS += \
    opengl_manager.h \
    openglwindows.h \
    rotation_scale_translate/rotation/rotate_2d.h \
    rotation_scale_translate/translate/translate.h \
    state_machine/game/game.h \
    state_machine/models/models.h \
    state_machine/state_machine.h \
    state_machine/state_of_model/state_of_model.h \
    vertex_group.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
