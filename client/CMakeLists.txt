cmake_minimum_required(VERSION 3.13)
project(PORTAL)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CLIENT_NAME "PORTAL")
set(SRC_FOLDER "src")

file(GLOB client_files
        "main.cpp"
	"../common/blocking_queue.cpp"
        "${SRC_FOLDER}/threads/blocking_queue_changes.cpp"
        "${SRC_FOLDER}/threads/game_proxy_thread.cpp"
        "${SRC_FOLDER}/threads/key_reader_thread.cpp"
        "${SRC_FOLDER}/threads/animation_loop_thread.cpp"
        "${SRC_FOLDER}/tests/animation_tests.cpp"
        "${SRC_FOLDER}/window/window.cpp"
        "${SRC_FOLDER}/window/os_exception.cpp"
        "${SRC_FOLDER}/common_texture/area.cpp"
        "${SRC_FOLDER}/common_texture/sdl_exception.cpp"
        "${SRC_FOLDER}/common_texture/big_texture.cpp"
        "${SRC_FOLDER}/common_texture/dynamic_sprite.cpp"
        "${SRC_FOLDER}/static_texture/static_texture.cpp"
        "${SRC_FOLDER}/chell_texture/chell_texture.cpp"
        "${SRC_FOLDER}/chell_texture/move_sense.cpp"
        "${SRC_FOLDER}/chell_texture/chell_sprites/chell_sprite_strategy.cpp"
        "${SRC_FOLDER}/chell_texture/chell_sprites/chell_run_right_sprite.cpp"
        "${SRC_FOLDER}/chell_texture/chell_sprites/chell_sweat_right_sprite.cpp"
	"${SRC_FOLDER}/chell_texture/chell_sprites/chell_jump_apex_right_sprite.cpp"
	"${SRC_FOLDER}/chell_texture/chell_sprites/chell_jump_rise_right_sprite.cpp"
	"${SRC_FOLDER}/chell_texture/chell_sprites/chell_jump_fall_right_sprite.cpp"
        )

add_executable(${CLIENT_NAME} ${client_files})

target_link_libraries(${CLIENT_NAME} SDL2 SDL2_image)

find_package(Threads REQUIRED)
target_link_libraries(${CLIENT_NAME} ${CMAKE_THREAD_LIBS_INIT})

install(FILES assets/all_blocks.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/all_chells_part_1.png DESTINATION ${CMAKE_BINARY_DIR})
