#-------------------------------------------------
#
# Project created by QtCreator 2016-12-19T22:22:04
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab7_1
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    order.cpp \
    client.cpp \
    employee.cpp

HEADERS  += mainwindow.h \
    order.h \
    client.h \
    employee.h

FORMS    += mainwindow.ui \
    order.ui \
    client.ui \
    employee.ui
