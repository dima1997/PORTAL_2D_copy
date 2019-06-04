cmake_minimum_required(VERSION 3.13)
project(PORTAL)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb")

# YAML
add_subdirectory(lib/yaml-cpp)
install(FILES common/configs_yaml/config_0.yaml DESTINATION ${CMAKE_BINARY_DIR})
install(FILES common/configs_yaml/config_1.yaml DESTINATION ${CMAKE_BINARY_DIR})

# SERVER -----------------------
set(SERVER_NAME "PORTAL-server")
set(SERVER_FOLDER "server")
file(GLOB server_files
        "${SERVER_FOLDER}/main.cpp"
        "${SERVER_FOLDER}/server/server.cpp"
        "${SERVER_FOLDER}/server/thread_pool.cpp"
        "${SERVER_FOLDER}/server/client_acceptor.cpp"
        "${SERVER_FOLDER}/server/request_executor.cpp"
        "${SERVER_FOLDER}/game/game.cpp"
        "${SERVER_FOLDER}/game/game_lobby.cpp"
        "${SERVER_FOLDER}/game/game_manager.cpp"
        "${SERVER_FOLDER}/game/map.cpp"
        "${SERVER_FOLDER}/game/world.cpp"
        "${SERVER_FOLDER}/game/player.cpp"
        "${SERVER_FOLDER}/game/body/body.cpp"
        "${SERVER_FOLDER}/game/body/block.cpp"
        "${SERVER_FOLDER}/game/body/chell.cpp"
        "${SERVER_FOLDER}/game/body/portal.cpp"
        "${SERVER_FOLDER}/game/body/cake.cpp"
        "${SERVER_FOLDER}/utils/id_generator.cpp"
        "${SERVER_FOLDER}/game/contact_listeners/contact_listener.cpp"
        )

add_executable(${SERVER_NAME} ${server_files})
target_compile_features(${SERVER_NAME} PUBLIC cxx_std_11)

add_subdirectory(lib/Box2D-cmake)
target_link_libraries(${SERVER_NAME} TG::Box2D)

add_subdirectory(common)
target_link_libraries(${SERVER_NAME} PORTAL::Common)

find_package(Threads REQUIRED)
target_link_libraries(${SERVER_NAME} ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(${SERVER_NAME} yaml-cpp)

# CLIENT ----------------------
set(CLIENT_NAME "PORTAL")
set(CLIENT_FOLDER "client")
file(GLOB client_files
        "${CLIENT_FOLDER}/main.cpp"
        "${CLIENT_FOLDER}/src/game/client.cpp"
        "${CLIENT_FOLDER}/src/game/game.cpp"
        "${CLIENT_FOLDER}/src/game/game_factory.cpp"
        "${CLIENT_FOLDER}/src/threads/playing_loop_thread.cpp"
        "${CLIENT_FOLDER}/src/threads/key_reader.cpp"
        "${CLIENT_FOLDER}/src/threads/event_game_processor.cpp"
        "${CLIENT_FOLDER}/src/threads/key_sender_thread.cpp"
        "${CLIENT_FOLDER}/src/threads/event_game_receiver_thread.cpp"
        "${CLIENT_FOLDER}/src/window/window.cpp"
        "${CLIENT_FOLDER}/src/window/texture_factory.cpp"
        "${CLIENT_FOLDER}/src/window/map_creator.cpp"
        "${CLIENT_FOLDER}/src/window/os_exception.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/area.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/texture.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/sprite_strategy.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/sdl_exception.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/big_texture.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/dynamic_sprite.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/texture_change.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/texture_move_change.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/texture_switch_change.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/null_sprite.cpp"
        "${CLIENT_FOLDER}/src/textures/block_metal_texture/block_metal_texture.cpp"
        "${CLIENT_FOLDER}/src/textures/block_metal_texture/block_metal_sprite_strategy.cpp"
        "${CLIENT_FOLDER}/src/textures/block_metal_texture/block_metal_sprite.cpp"
        "${CLIENT_FOLDER}/src/textures/block_rock_texture/block_rock_texture.cpp"
        "${CLIENT_FOLDER}/src/textures/block_rock_texture/block_rock_sprite.cpp"
        "${CLIENT_FOLDER}/src/textures/block_acid_texture/block_acid_texture.cpp"
        "${CLIENT_FOLDER}/src/textures/block_acid_texture/block_acid_sprite.cpp"
        "${CLIENT_FOLDER}/src/textures/static_texture/static_texture.cpp"
        "${CLIENT_FOLDER}/src/textures/chell_texture/chell_texture.cpp"
        "${CLIENT_FOLDER}/src/textures/chell_texture/move_sense.cpp"
        "${CLIENT_FOLDER}/src/textures/chell_texture/chell_sprite_strategy.cpp"
        "${CLIENT_FOLDER}/src/textures/chell_texture/chell_run_right_sprite.cpp"
        "${CLIENT_FOLDER}/src/textures/chell_texture/chell_sweat_right_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/chell_texture/chell_jump_apex_right_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/chell_texture/chell_jump_rise_right_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/chell_texture/chell_jump_fall_right_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/portal_texture/portal_blue_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/portal_texture/portal_orange_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/portal_texture/portal_sprite_strategy.cpp"
	"${CLIENT_FOLDER}/src/textures/portal_texture/portal_blue_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/door_texture/door_one_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/door_texture/door_one_closed_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/door_texture/door_two_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/door_texture/door_two_closed_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/door_texture/door_three_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/door_texture/door_three_closed_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/door_texture/door_four_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/door_texture/door_four_closed_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/door_texture/door_five_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/door_texture/door_five_closed_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/button_texture/button_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/button_texture/button_sprite_strategy.cpp"
	"${CLIENT_FOLDER}/src/textures/button_texture/button_unpressed_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/button_texture/button_pressed_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/energy_ball_texture/energy_ball_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/energy_ball_texture/energy_ball_sprite_strategy.cpp"
	"${CLIENT_FOLDER}/src/textures/energy_ball_texture/energy_ball_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/rock_texture/rock_one_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/rock_texture/rock_one_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/barrier_texture/barrier_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/barrier_texture/barrier_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/triangle_texture/triangle_botom_left_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/triangle_texture/triangle_botom_left_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/triangle_texture/triangle_botom_right_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/triangle_texture/triangle_botom_right_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/triangle_texture/triangle_top_left_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/triangle_texture/triangle_top_left_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/triangle_texture/triangle_top_right_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/triangle_texture/triangle_top_right_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/receiver_texture/receiver_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/receiver_texture/receiver_on_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/receiver_texture/receiver_off_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/receiver_texture/receiver_unlocking_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/receiver_texture/receiver_sprite_strategy.cpp"
	"${CLIENT_FOLDER}/src/textures/emitter_texture/emitter_right_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/emitter_texture/emitter_right_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/cake_texture/cake_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/cake_texture/cake_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/background_texture/background_one_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/background_texture/background_one_sprite.cpp"
        )

add_executable(${CLIENT_NAME} ${common_files} ${client_files})

target_compile_features(${CLIENT_NAME} PUBLIC cxx_std_11)
target_link_libraries(${CLIENT_NAME} PORTAL::Common)

find_package(Threads REQUIRED)
target_link_libraries(${CLIENT_NAME} ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(${CLIENT_NAME} SDL2 SDL2_image)

target_link_libraries(${CLIENT_NAME} yaml-cpp)

install(FILES client/assets/all_blocks.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/all_chells_part_1.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/portal_white.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/doors.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/rocks_and_balls.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/button_sprites.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/barrier.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/all_triangles.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/cake.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/background_1.png DESTINATION ${CMAKE_BINARY_DIR})
