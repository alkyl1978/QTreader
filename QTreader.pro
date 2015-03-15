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
    serialport.cpp \
    form.cpp

HEADERS  += \
    serialport.h \
    form.h

FORMS    += \
    form.ui

RESOURCES +=
