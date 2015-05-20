#-------------------------------------------------
#
# Project created by QtCreator 2014-12-13T12:18:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QFile
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    paint.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    paint.h

FORMS    += mainwindow.ui \
    dialog.ui \
    paint.ui
