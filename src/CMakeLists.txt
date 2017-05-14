set(SOURCE_FILES
        main.cpp
        net/poller.cpp
        util/config.cpp
        module/mylog/log.cpp
        module/mylog/log_wrapper.cpp
        svr/luna_server.cpp
        svr/luna_master.cpp
        svr/luna_master.h
        svr/luna_worker.cpp
        svr/luna_worker.h)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH, ${PROJETC_BINARY_DIR})

add_executable(luna ${SOURCE_FILES})