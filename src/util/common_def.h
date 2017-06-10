#ifndef COMMON_DEF_H
#define COMMON_DEF_H

// if someday i have to implition luna_list myself
#define DEF_LUNA_LIST \
    #include <vector> \
    using std::vector = LunaList;

namespace luna {

class RuntimeManager;
using RuntimeManager = RuntimeManager;
using RuntimeManagerPtr = RuntimeManager*;

class NetManager;
using NetManager = NetManager;
using NetManagerPtr = NetManager*;

class TcpManager;
using TcpManager = TcpManager;
using TcpManagerPtr = TcpManager*;

class TcpListener;
using TcpListener = TcpListener;
using TcpListenerPtr = TcpListener*;

class TcpConnection;
using TcpConnection = TcpConnection;
using TcpConnectionPtr = TcpConnection*;
}


#endif // COMMON_DEF_H
