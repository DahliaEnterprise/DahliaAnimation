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
    vertex_group.cpp

HEADERS += \
    opengl_manager.h \
    openglwindows.h \
    rotation_scale_translate/rotation/rotate_2d.h \
    vertex_group.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
