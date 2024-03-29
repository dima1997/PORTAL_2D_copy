cmake_minimum_required(VERSION 3.13)
project(PORTAL)

set(CMAKE_CXX_STANDARD 11)
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb -DDEBUG -fno-inline -fno-stack-protector -Wall -Werror -pedantic -pedantic-errors")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb -DDEBUG")

# YAML
add_subdirectory(lib/yaml-cpp)

# SERVER -----------------------
set(SERVER_NAME "PORTAL-server")
set(SERVER_FOLDER "server")
file(GLOB server_files
        "${SERVER_FOLDER}/main.cpp"
        "${SERVER_FOLDER}/config/global_configuration.cpp"
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
        "${SERVER_FOLDER}/game/client_action/client_action.cpp"
        "${SERVER_FOLDER}/game/client_action/client_coord_action.cpp"
        "${SERVER_FOLDER}/game/client_action/pin_tool_action.cpp"
        "${SERVER_FOLDER}/game/client_action/open_portal_action.cpp"
        "${SERVER_FOLDER}/game/client_action/quit_game_action.cpp"
        "${SERVER_FOLDER}/game/client_action/move_left_action.cpp"
        "${SERVER_FOLDER}/game/client_action/move_right_action.cpp"
        "${SERVER_FOLDER}/game/client_action/throw_right_action.cpp"
        "${SERVER_FOLDER}/game/client_action/throw_left_action.cpp"
        "${SERVER_FOLDER}/game/client_action/jump_action.cpp"
        "${SERVER_FOLDER}/game/client_action/kill_action.cpp"
        "${SERVER_FOLDER}/game/client_action/stop_move_action.cpp"
        "${SERVER_FOLDER}/game/client_action/grab_rock_action.cpp"
        "${SERVER_FOLDER}/game/client_action/reset_portals_action.cpp"
        "${SERVER_FOLDER}/game/model/body.cpp"
        "${SERVER_FOLDER}/game/model/block.cpp"
        "${SERVER_FOLDER}/game/model/chell.cpp"
        "${SERVER_FOLDER}/game/model/portal.cpp"
        "${SERVER_FOLDER}/game/model/cake.cpp"
        "${SERVER_FOLDER}/game/model/button.cpp"
        "${SERVER_FOLDER}/game/model/door.cpp"
        "${SERVER_FOLDER}/game/model/rock.cpp"
        "${SERVER_FOLDER}/game/model/barrier.cpp"
        "${SERVER_FOLDER}/game/model/energy_emitter.cpp"
        "${SERVER_FOLDER}/game/model/energy_receiver.cpp"
        "${SERVER_FOLDER}/game/model/energy_ball.cpp"
        "${SERVER_FOLDER}/game/model/pin_tool.cpp"
        "${SERVER_FOLDER}/game/model/movable_body.cpp"
        "${SERVER_FOLDER}/game/model/switchable.cpp"
        "${SERVER_FOLDER}/game/ray_cast_callback/portal_ray_cast_callback.cpp"
        "${SERVER_FOLDER}/utils/geometry_utils.cpp"
        "${SERVER_FOLDER}/game/contact_listener/contact_listener.cpp"
        "${SERVER_FOLDER}/game/contact_filter/contact_filter.cpp"
        )

install(FILES server/config/server_config.yaml DESTINATION ${CMAKE_BINARY_DIR})
install(FILES server/config/map_0.yaml DESTINATION ${CMAKE_BINARY_DIR})
install(FILES server/config/map_1.yaml DESTINATION ${CMAKE_BINARY_DIR})
install(FILES server/config/map_2.yaml DESTINATION ${CMAKE_BINARY_DIR})
install(FILES server/config/map_3.yaml DESTINATION ${CMAKE_BINARY_DIR})
install(FILES server/config/map_4.yaml DESTINATION ${CMAKE_BINARY_DIR})
install(FILES server/config/map_5.yaml DESTINATION ${CMAKE_BINARY_DIR})

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

find_package(Qt5Widgets)
qt5_wrap_ui(UIS_HEADERS
	"${CLIENT_FOLDER}/src/user_interface/uis/GameOver.ui"
	"${CLIENT_FOLDER}/src/user_interface/uis/Login.ui"
	"${CLIENT_FOLDER}/src/user_interface/uis/LoginNew.ui"
	"${CLIENT_FOLDER}/src/user_interface/uis/LoginJoin.ui"
	"${CLIENT_FOLDER}/src/user_interface/uis/LoginMode.ui"
	"${CLIENT_FOLDER}/src/user_interface/uis/LoginServer.ui"
)

qt5_add_resources(UIS_RC
    "${CLIENT_FOLDER}/assets/resources.qrc"
)

include_directories(${PROJECT_BINARY_DIR})

file(GLOB client_files
        "${CLIENT_FOLDER}/main.cpp"
        "${CLIENT_FOLDER}/src/game/client.cpp"
        "${CLIENT_FOLDER}/src/game/game.cpp"
        "${CLIENT_FOLDER}/src/game/game_config.cpp"
        "${CLIENT_FOLDER}/src/game/game_factory.cpp"
        "${CLIENT_FOLDER}/src/threads/playing_loop_thread.cpp"
        "${CLIENT_FOLDER}/src/threads/play_result.cpp"
        "${CLIENT_FOLDER}/src/threads/key_reader.cpp"
        "${CLIENT_FOLDER}/src/threads/event_game_processor.cpp"
        "${CLIENT_FOLDER}/src/threads/key_sender_thread.cpp"
        "${CLIENT_FOLDER}/src/threads/event_game_receiver_thread.cpp"
        "${CLIENT_FOLDER}/src/window/window.cpp"
        "${CLIENT_FOLDER}/src/window/texture_factory.cpp"
        "${CLIENT_FOLDER}/src/window/map_creator.cpp"
        "${CLIENT_FOLDER}/src/window/os_exception.cpp"
        "${CLIENT_FOLDER}/src/window/changes/change.cpp"
        "${CLIENT_FOLDER}/src/window/changes/start_game_change.cpp"
        "${CLIENT_FOLDER}/src/window/changes/texture_move_change.cpp"
        "${CLIENT_FOLDER}/src/window/changes/portal_move_change.cpp"
        "${CLIENT_FOLDER}/src/window/changes/texture_switch_change.cpp"
        "${CLIENT_FOLDER}/src/window/changes/start_follow_change.cpp"
        "${CLIENT_FOLDER}/src/window/changes/stop_follow_change.cpp"
        "${CLIENT_FOLDER}/src/window/changes/player_dies_change.cpp"
        "${CLIENT_FOLDER}/src/window/changes/player_reach_cake_change.cpp"
        "${CLIENT_FOLDER}/src/window/changes/player_wins_change.cpp"
        "${CLIENT_FOLDER}/src/window/changes/player_loses_change.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/area.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/texture.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/sprite_strategy.cpp"
	"${CLIENT_FOLDER}/src/textures/common_texture/two_sprites_strategy.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/sdl_exception.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/big_texture.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/dynamic_sprite.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/null_sprite.cpp"
        "${CLIENT_FOLDER}/src/textures/common_texture/null_end_strategy.cpp"
        "${CLIENT_FOLDER}/src/textures/block_metal_texture/block_metal_sprite.cpp"
        "${CLIENT_FOLDER}/src/textures/block_rock_texture/block_rock_sprite.cpp"
        "${CLIENT_FOLDER}/src/textures/block_acid_texture/block_acid_sprite.cpp"
        "${CLIENT_FOLDER}/src/textures/chell_texture/chell_texture.cpp"
        "${CLIENT_FOLDER}/src/textures/chell_texture/move_sense.cpp"
        "${CLIENT_FOLDER}/src/textures/chell_texture/chell_sprite_strategy.cpp"
        "${CLIENT_FOLDER}/src/textures/chell_texture/chell_dead_strategy.cpp"
        "${CLIENT_FOLDER}/src/textures/chell_texture/chell_run_right_sprite.cpp"
        "${CLIENT_FOLDER}/src/textures/chell_texture/chell_stand_right_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/chell_texture/chell_jump_apex_right_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/chell_texture/chell_jump_rise_right_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/chell_texture/chell_jump_fall_right_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/chell_texture/chell_dying_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/chell_texture/chell_point_right_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/chell_texture/chell_cake_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/portal_texture/portal_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/portal_texture/portal_sprite_strategy.cpp"
	"${CLIENT_FOLDER}/src/textures/portal_texture/portal_white_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/door_texture/door_one_sprite_strategy.cpp"
	"${CLIENT_FOLDER}/src/textures/door_texture/door_one_closed_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/door_texture/door_one_opened_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/door_texture/door_one_opening_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/button_texture/button_sprite_strategy.cpp"
	"${CLIENT_FOLDER}/src/textures/button_texture/button_unpressed_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/button_texture/button_pressed_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/energy_ball_texture/energy_ball_sprite_strategy.cpp"
	"${CLIENT_FOLDER}/src/textures/energy_ball_texture/energy_ball_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/rock_texture/rock_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/barrier_texture/barrier_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/triangle_texture/triangle_botom_left_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/receiver_texture/receiver_on_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/receiver_texture/receiver_off_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/receiver_texture/receiver_unlocking_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/receiver_texture/receiver_sprite_strategy.cpp"
	"${CLIENT_FOLDER}/src/textures/emitter_texture/emitter_right_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/cake_texture/cake_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/background_texture/background_one_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/pin_tool_texture/pin_tool_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/record_texture/recording_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/record_texture/record_texture.cpp"
	"${CLIENT_FOLDER}/src/textures/loading_texture/loading_sprite.cpp"
	"${CLIENT_FOLDER}/src/textures/loading_texture/loading_texture.cpp"
	"${CLIENT_FOLDER}/src/user_interface/line_interface.cpp"
	"${CLIENT_FOLDER}/src/user_interface/message_exception.cpp"
	"${CLIENT_FOLDER}/src/mixer/mixer.cpp"
	"${CLIENT_FOLDER}/src/mixer/mix_chunck.cpp"
	"${CLIENT_FOLDER}/src/mixer/mix_music.cpp"
	"${CLIENT_FOLDER}/src/mixer/portal_mixer.cpp"
	"${CLIENT_FOLDER}/src/sdl_system.cpp"
	"${CLIENT_FOLDER}/src/window/record/format_context.cpp"
	"${CLIENT_FOLDER}/src/window/record/codec_context_wrapper.cpp"
	"${CLIENT_FOLDER}/src/window/record/sws_context_wrapper.cpp"
	"${CLIENT_FOLDER}/src/window/record/output_format.cpp"
	"${CLIENT_FOLDER}/src/threads/video_record_thread.cpp"
	"${CLIENT_FOLDER}/src/user_interface/game_over.cpp"
	"${CLIENT_FOLDER}/src/user_interface/login.cpp"
	"${CLIENT_FOLDER}/src/user_interface/login_server.cpp"
	"${CLIENT_FOLDER}/src/user_interface/login_mode.cpp"
	"${CLIENT_FOLDER}/src/user_interface/login_new.cpp"
	"${CLIENT_FOLDER}/src/user_interface/login_join.cpp"
        )

add_executable(${CLIENT_NAME} ${common_files} ${client_files} ${UIS_HEADERS} ${UIS_RC})  

target_compile_features(${CLIENT_NAME} PUBLIC cxx_std_11)
target_link_libraries(${CLIENT_NAME} PORTAL::Common)

find_package(Threads REQUIRED)
target_link_libraries(${CLIENT_NAME} ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(${CLIENT_NAME} SDL2 SDL2_image SDL2_mixer)

target_link_libraries(${CLIENT_NAME} yaml-cpp)

target_link_libraries(${CLIENT_NAME} Qt5::Widgets)

target_link_libraries(${CLIENT_NAME} avformat avcodec avutil swscale)

install(FILES client/assets/only_blocks.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/all_chells_half.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/white_portal.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/doors.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/balls_and_rocks.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/button_sprites.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/barrier.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/cake.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/portal_radio.wav DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/portal_shoot.wav DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/dying.wav DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/jump.wav DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/portal_background_3.jpg DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/pin_tool.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES client/assets/loading_3.png DESTINATION ${CMAKE_BINARY_DIR})
