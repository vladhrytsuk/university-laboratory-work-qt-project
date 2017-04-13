#-------------------------------------------------
#
# Project created by QtCreator 2015-11-22T16:42:41
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab7
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    product.cpp \
    customer.cpp \
    buyerofgoods.cpp

HEADERS  += mainwindow.h \
    product.h \
    customer.h \
    buyerofgoods.h

FORMS    += mainwindow.ui \
    product.ui \
    customer.ui \
    buyerofgoods.ui
