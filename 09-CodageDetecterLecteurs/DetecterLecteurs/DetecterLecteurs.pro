# -------------------------------------------------
# Project created by QtCreator 2013-02-28T23:20:18
# -------------------------------------------------
QT += network \
    sql
TARGET = DetecterLecteurs
TEMPLATE = app
SOURCES += main.cpp \
    detecterlecteurs.cpp \
    tcpserver.cpp \
    tcpserverthread.cpp \
    readerdetector.cpp \
    reader.cpp
HEADERS += detecterlecteurs.h \
    tcpserver.h \
    tcpserverthread.h \
    readerdetector.h \
    reader.h
FORMS += detecterlecteurs.ui
