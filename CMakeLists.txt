cmake_minimum_required(VERSION 3.13)
project(PORTAL)

set(CMAKE_CXX_STANDARD 11)

# COMMON -----------------------
set(COMMON_FOLDER "common")
file(GLOB common_files
        "${COMMON_FOLDER}/socket_exception.cpp"
        "${COMMON_FOLDER}/socket.cpp"
        "${COMMON_FOLDER}/blocking_queue.cpp"
        )

# SERVER -----------------------
set(SERVER_NAME "PORTAL_server")
set(SERVER_FOLDER "server")
file(GLOB server_files
        "${SERVER_FOLDER}/main.cpp"
        )

add_executable(${SERVER_NAME} ${common_files} ${server_files})

add_subdirectory(lib/Box2D)
target_compile_features(${SERVER_NAME} PUBLIC cxx_std_17)
target_link_libraries(${SERVER_NAME} TG::Box2D)

find_package(Threads REQUIRED)
target_link_libraries(${SERVER_NAME} ${CMAKE_THREAD_LIBS_INIT})

# CLIENT ----------------------
set(CLIENT_NAME "PORTAL")
set(CLIENT_FOLDER "client")
file(GLOB client_files
        "${CLIENT_FOLDER}/main.cpp"
        )

add_executable(${CLIENT_NAME} ${common_files} ${client_files})

