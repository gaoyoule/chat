#-------------------------------------------------
#
# Project created by QtCreator 2023-10-09T11:13:16
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test10_server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    CJsonObject.cpp \
    cJSON.c \
    MsgBuilder.cpp \
    userdao.cpp \
    myserver.cpp \
    socketthread.cpp

HEADERS  += mainwindow.h \
    cJSON.h \
    CJsonObject.hpp \
    MsgBuilder.h \
    userdao.h \
    myserver.h \
    socketthread.h

FORMS    += mainwindow.ui
