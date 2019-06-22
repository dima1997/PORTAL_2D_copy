cmake_minimum_required(VERSION 3.13)
project(PORTAL-common)

set(SOURCES
        "${PROJECT_SOURCE_DIR}/connector/socket_exception.cpp"
        "${PROJECT_SOURCE_DIR}/connector/socket.cpp"
        "${PROJECT_SOURCE_DIR}/connector/connector.cpp"
        "${PROJECT_SOURCE_DIR}/blocking_queue.cpp"
	"${PROJECT_SOURCE_DIR}/blocking_queue.h"
        "${PROJECT_SOURCE_DIR}/portal_exception.cpp"
        "${PROJECT_SOURCE_DIR}/protocol/event/event.cpp"
        "${PROJECT_SOURCE_DIR}/protocol/event/object_moves_event.cpp"
        "${PROJECT_SOURCE_DIR}/protocol/event/object_switch_event.cpp"
        "${PROJECT_SOURCE_DIR}/protocol/event/player_wins_event.cpp"
        "${PROJECT_SOURCE_DIR}/protocol/event/player_loses_event.cpp"
        "${PROJECT_SOURCE_DIR}/protocol/event/player_dies_event.cpp"
        "${PROJECT_SOURCE_DIR}/protocol/event/grab_rock_event.cpp"
        "${PROJECT_SOURCE_DIR}/protocol/event/throw_rock_event.cpp"
        "${PROJECT_SOURCE_DIR}/protocol/event/game_starts_event.cpp"
        "${PROJECT_SOURCE_DIR}/protocol/event/portal_moves_event.cpp"
        "${PROJECT_SOURCE_DIR}/protocol/event/player_reach_cake_event.cpp"
        "${PROJECT_SOURCE_DIR}/thread.cpp"
        "${PROJECT_SOURCE_DIR}/thread_safe_queue.cpp"
        "${PROJECT_SOURCE_DIR}/thread_safe_queue.h"
        "${PROJECT_SOURCE_DIR}/protocol/game_action/game_action.cpp"
        "${PROJECT_SOURCE_DIR}/protocol/game_action/coords_action.cpp"
	"${PROJECT_SOURCE_DIR}/configs_yaml/config_paths.h"
        )

add_library(${PROJECT_NAME} STATIC ${SOURCES})
add_library(PORTAL::Common ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME} PUBLIC .)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
