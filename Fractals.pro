#-------------------------------------------------
#
# Project created by QtCreator 2017-10-01T09:36:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fractals
TEMPLATE = app

SOURCES += \
        main.cpp \
        mainWindow.cpp \
    graphic/paintWidget.cpp \
    library/fractal.cpp \
    library/mandelbrot.cpp \
    library/palette.cpp

HEADERS += \
        mainWindow.h \
    graphic/paintWidget.h \
    library/fractal.h \
    library/mandelbrot.h \
    library/palette.h

FORMS += \
        mainWindow.ui

CONFIG += c++11
