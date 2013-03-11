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
    readerclient.cpp \
    reader.cpp \
    readerdetector.cpp
HEADERS += detecterlecteurs.h \
    tcpserverthread.h \
    readerclient.h \
    reader.h \
    readerdetector.h
FORMS += detecterlecteurs.ui
