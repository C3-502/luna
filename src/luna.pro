TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = luna
DESTDIR = ../build/bin
OBJECTS_DIR = ../build/objs


SOURCES += main.cpp \
    util/config.cpp \
    net/poller.cpp \
    svr/luna_server.cpp

HEADERS += \
    util/config.h \
    net/event_base.h \
    net/poller.h \
    util/const.h \
    svr/luna_server.h

