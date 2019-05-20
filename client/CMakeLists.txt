cmake_minimum_required(VERSION 3.13)
project(PORTAL)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CLIENT_NAME "PORTAL")
set(SRC_FOLDER "src")

file(GLOB client_files
        "main.cpp"
        "${SRC_FOLDER}/animation_tests.cpp"
        "${SRC_FOLDER}/window.cpp"
        "${SRC_FOLDER}/area.cpp"
        "${SRC_FOLDER}/sdl_exception.cpp"
        "${SRC_FOLDER}/os_exception.cpp"
        "${SRC_FOLDER}/big_texture.cpp"
        "${SRC_FOLDER}/static_texture.cpp"
        "${SRC_FOLDER}/chell_texture.cpp"
        "${SRC_FOLDER}/move_sense.cpp"
        "${SRC_FOLDER}/chell_sprite_strategy.cpp"
        "${SRC_FOLDER}/dynamic_sprite.cpp"
        "${SRC_FOLDER}/chell_run_right_sprite.cpp"
        "${SRC_FOLDER}/chell_sweat_right_sprite.cpp"
        )

add_executable(${CLIENT_NAME} ${client_files})

target_link_libraries(${CLIENT_NAME} SDL2 SDL2_image)

install(FILES assets/all_blocks.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/all_chells_part_1.png DESTINATION ${CMAKE_BINARY_DIR})
