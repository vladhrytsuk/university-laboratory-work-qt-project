#-------------------------------------------------
#
# Project created by QtCreator 2015-10-14T16:19:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab4
TEMPLATE = app


SOURCES += main.cpp\
        texteditor.cpp \
    searchdialog.cpp

HEADERS  += texteditor.h \
    searchdialog.h

FORMS    += texteditor.ui \
    searchdialog.ui

RESOURCES += \
    texteditor.qrc
