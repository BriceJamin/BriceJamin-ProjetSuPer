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
    readerdata.cpp \
    reader.cpp
HEADERS += detecterlecteurs.h \
    tcpserverthread.h \
    readerdetector.h \
    readerdata.h \
    reader.h
FORMS += detecterlecteurs.ui
