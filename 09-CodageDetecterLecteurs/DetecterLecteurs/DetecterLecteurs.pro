# -------------------------------------------------
# Project created by QtCreator 2013-02-28T23:20:18
# -------------------------------------------------
QT += network \
    sql
TARGET = DetecterLecteurs
TEMPLATE = app
SOURCES += main.cpp \
    detecterlecteurs.cpp \
    tcpserverthread.cpp \
    readerdetector.cpp \
    reader.cpp \
    thread.cpp
HEADERS += detecterlecteurs.h \
    tcpserverthread.h \
    readerdetector.h \
    reader.h \
    thread.h
FORMS += detecterlecteurs.ui
