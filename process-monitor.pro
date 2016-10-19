#-------------------------------------------------
#
# Project created by QtCreator 2016-10-19T19:30:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = process-monitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    processitem.cpp

HEADERS  += mainwindow.h \
    processitem.h

FORMS    += mainwindow.ui
