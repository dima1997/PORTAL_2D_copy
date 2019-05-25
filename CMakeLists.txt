cmake_minimum_required(VERSION 3.13)
project(PORTAL)

set(CMAKE_CXX_STANDARD 11)

# COMMON -----------------------
set(COMMON_FOLDER "common")
file(GLOB common_files
        "${COMMON_FOLDER}/socket_exception.cpp"
        "${COMMON_FOLDER}/socket.cpp"
        "${COMMON_FOLDER}/blocking_queue.cpp"
        "${COMMON_FOLDER}/connector.cpp"
        "${COMMON_FOLDER}/portal_exception.cpp"
        "${COMMON_FOLDER}/protocol/event.cpp"
        "${COMMON_FOLDER}/protocol/object_moves_event.cpp"
        )

# SERVER -----------------------
set(SERVER_NAME "PORTAL_server")
set(SERVER_FOLDER "server")
file(GLOB server_files
        "${SERVER_FOLDER}/main.cpp"
        "${SERVER_FOLDER}/server.cpp"
        "${SERVER_FOLDER}/thread_pool.cpp"
        "${SERVER_FOLDER}/client_acceptor.cpp"
        "${SERVER_FOLDER}/request_executor.cpp"
        "${SERVER_FOLDER}/game.cpp"
        "${SERVER_FOLDER}/game_manager.cpp"
        "${SERVER_FOLDER}/world.cpp"
        "${SERVER_FOLDER}/player.cpp"
        "${SERVER_FOLDER}/body/body.cpp"
        "${SERVER_FOLDER}/body/rock_block.cpp"
        "${SERVER_FOLDER}/body/chell.cpp"
        "${SERVER_FOLDER}/id_generator.cpp"
        )

add_executable(${SERVER_NAME} ${common_files} ${server_files})

add_subdirectory(lib/Box2D-cmake)
target_compile_features(${SERVER_NAME} PUBLIC cxx_std_17)
target_link_libraries(${SERVER_NAME} TG::Box2D)

find_package(Threads REQUIRED)
target_link_libraries(${SERVER_NAME} ${CMAKE_THREAD_LIBS_INIT})

# CLIENT ----------------------
set(CLIENT_NAME "PORTAL")
set(CLIENT_FOLDER "client")
file(GLOB client_files
        "${CLIENT_FOLDER}/main.cpp"
        "${CLIENT_FOLDER}/client.cpp"
        "${CLIENT_FOLDER}/game.cpp"
        "${CLIENT_FOLDER}/game_factory.cpp"
        )

add_executable(${CLIENT_NAME} ${common_files} ${client_files})

