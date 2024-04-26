#-------------------------------------------------
#
# Project created by QtCreator 2023-10-08T16:21:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test10_chatroom
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp \
    registerdialog.cpp \
    CJsonObject.cpp \
    cJSON.c \
    MsgBuilder.cpp \
    mysocket.cpp \
    friendsdialog.cpp \
    friendform.cpp \
    ChatWidget.cpp \
    ChatItem.cpp \
    chatdialog.cpp \
    caipiao.cpp \
    caishuzi.cpp \
    more.cpp \
    jisuanqi.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    registerdialog.h \
    cJSON.h \
    CJsonObject.hpp \
    MsgBuilder.h \
    mysocket.h \
    friendsdialog.h \
    friendform.h \
    ChatWidget.h \
    ChatItem.h \
    chatdialog.h \
    caipiao.h \
    caishuzi.h \
    more.h \
    jisuanqi.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    registerdialog.ui \
    friendsdialog.ui \
    friendform.ui \
    chatdialog.ui \
    caipiao.ui \
    caishuzi.ui \
    more.ui \
    jisuanqi.ui

RESOURCES += \
    img.qrc

DISTFILES +=
