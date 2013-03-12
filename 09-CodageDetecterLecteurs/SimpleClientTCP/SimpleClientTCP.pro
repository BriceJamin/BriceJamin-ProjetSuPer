#-------------------------------------------------
#
# Project created by QtCreator 2013-03-11T17:49:23
#
#-------------------------------------------------

QT += core \
      gui \
      network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleClientTCP
TEMPLATE = app


SOURCES += \
    clienttcp.cpp \
    main.cpp \
    mainwindow.cpp \
    clienttcpwindow.cpp

HEADERS  += \
    clienttcp.h \
    mainwindow.h \
    clienttcpwindow.h

FORMS    += \
    clienttcpwindow.ui \
    mainwindow.ui
