#-------------------------------------------------
#
# Project created by QtCreator 2015-03-05T13:58:47
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTreader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialport.cpp

HEADERS  += mainwindow.h \
    serialport.h

FORMS    += mainwindow.ui
