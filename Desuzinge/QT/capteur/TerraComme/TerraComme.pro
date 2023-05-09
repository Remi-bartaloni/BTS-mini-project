#-------------------------------------------------
#
# Project created by QtCreator 2018-11-08T14:52:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TerraComme
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client_tcp.cpp \
    parser.cpp \
    mesures.cpp \
    mythread.cpp \
    port_serie.cpp

HEADERS  += mainwindow.h \
    client_tcp.h \
    parser.h \
    mesures.h \
    mythread.h \
    port_serie.h

FORMS    += mainwindow.ui
