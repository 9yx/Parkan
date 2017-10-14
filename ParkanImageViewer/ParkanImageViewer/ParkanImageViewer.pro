#-------------------------------------------------
#
# Project created by QtCreator 2017-10-10T23:08:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ParkanImageViewer
TEMPLATE = app


SOURCES += main.cpp\
        viewer_app.cpp \
    binary_file.cpp \
    palette.cpp \
    texture.cpp \
    color_ramp_widget.cpp

HEADERS  += viewer_app.h \
    binary_file.h \
    palette.h \
    texture.h \
    color_ramp_widget.h

FORMS    += viewer_app.ui
