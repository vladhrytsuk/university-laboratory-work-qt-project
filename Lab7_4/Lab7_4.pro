#-------------------------------------------------
#
# Project created by QtCreator 2016-12-21T13:15:42
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab7_4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    department.cpp \
    trolleybus.cpp \
    personal.cpp

HEADERS  += mainwindow.h \
    department.h \
    trolleybus.h \
    personal.h

FORMS    += mainwindow.ui \
    department.ui \
    trolleybus.ui \
    personal.ui
