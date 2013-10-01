#-------------------------------------------------
#
# Project created by QtCreator 2010-12-08T20:14:09
#
#-------------------------------------------------

QT       += core gui

TARGET = Sokoban
TEMPLATE = app


SOURCES += main.cpp\
    mapbuilder.cpp \
    sokobanview.cpp \
    sokobanwindow.cpp \
    leveldialog.cpp \
    itemlist.cpp \
    infowidget.cpp \
    editorwidget.cpp \
    movestepcommand.cpp

HEADERS  += \
    mapbuilder.h \
    sprites.h \
    sokobanview.h \
    sokobanwindow.h \
    leveldialog.h \
    itemlist.h \
    infowidget.h \
    editorwidget.h \
    movestepcommand.h

FORMS    += \
    sokobanwindow.ui \
    leveldialog.ui \
    infowidget.ui \
    editorwidget.ui
QT	+= xml

RESOURCES += \
    sokobanResource.qrc
