# -------------------------------------------------
# Project created by QtCreator 2013-03-28T15:57:49
# -------------------------------------------------
QT += core \
    gui \
    network
greaterThan(QT_MAJOR_VERSION, 4):QT += widgets
TARGET = MonoThread
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    server.cpp \
    tcpserver.cpp \
    clientmanager.cpp \
    thread.cpp \
    tcpsocket.cpp
HEADERS += mainwindow.h \
    server.h \
    tcpserver.h \
    clientmanager.h \
    thread.h \
    tcpsocket.h
FORMS += mainwindow.ui
