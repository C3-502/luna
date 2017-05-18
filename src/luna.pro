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
    svr/luna_process.cpp \
    svr/runtime_manager.cpp \
    svr/net_manager.cpp \
    net/poller.cpp \
    net/tcp_listener.cpp \
    net/event/tcp_listener.cpp \
    net/tcp_manager.cpp \
    net/event/tcp_connection.cpp \
    net/ipv4_addr.cpp

HEADERS += \
    svr/luna_server.h \
    util/common_inc.h \
    svr/luna_process.h \
    svr/runtime_manager.h \
    util/config.h \
    util/const.h \
    util/noncopyable.h \
    svr/net_manager.h \
    net/poller.h \
    net/tcp_listener.h \
    net/event/event_base.h \
    net/event/tcp_listener.h \
    net/tcp_manager.h \
    util/common_def.h \
    net/event/tcp_connection.h \
    net/ipv4_addr.h

