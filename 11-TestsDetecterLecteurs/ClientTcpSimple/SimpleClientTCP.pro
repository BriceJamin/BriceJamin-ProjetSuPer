# -------------------------------------------------
# Project created by QtCreator 2013-03-11T17:49:23
# -------------------------------------------------
QT += core \
    gui \
    network
greaterThan(QT_MAJOR_VERSION, 4):QT += widgets
TARGET = SimpleClientTCP
TEMPLATE = app
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    clienttcpwindow.cpp \
    clienttcp.cpp
HEADERS += \
    mainwindow.h \
    clienttcpwindow.h \
    clienttcp.h
FORMS += \
    mainwindow.ui \
    clienttcpwindow.ui