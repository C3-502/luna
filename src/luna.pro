TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = luna
DESTDIR = ../build/bin
OBJECTS_DIR = ../build/objs

SOURCES += main.cpp \
    svr/luna_server.cpp \
    module/log/src/log.cpp \
    module/log/src/log_wrapper.cpp \
    util/config.cpp \
    svr/luna_master.cpp \
    svr/luna_worker.cpp

HEADERS += \
    svr/luna_master.h \
    svr/luna_server.h \
    svr/luna_worker.h

