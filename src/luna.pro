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
    net/event/tcp_listener.cpp \
    net/tcp_manager.cpp \
    net/event/tcp_connection.cpp \
    net/ipv4_addr.cpp \
    svr/luna_runtime_api.cpp \
    net/event/event_base.cpp \
    util/buffer.cpp \
    net/socket.cpp \
    parser/http/httpparser.cpp \
    parser/http/httpconnection.cpp \
    parser/http/httprequest.cpp \
    parser/http/httpresponse.cpp \
    parser/http/httphandler.cpp \
    parser/http/http_parser.c \
    parser/http/httpcommon.cpp

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
    net/event/event_base.h \
    net/event/tcp_listener.h \
    net/tcp_manager.h \
    util/common_def.h \
    net/event/tcp_connection.h \
    net/ipv4_addr.h \
    svr/luna_runtime_api.h \
    util/buffer.h \
    net/socket.h \
    parser/http/httpparser.h \
    parser/http/httpconnection.h \
    parser/http/httprequest.h \
    parser/http/httpcommon.h \
    parser/http/httpresponse.h \
    parser/http/httphandler.h \
    parser/http/http_parser.h

