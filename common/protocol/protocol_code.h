//
// Created by franciscosicardi on 09/05/19.
//

#ifndef TP3_TALLER_PROTOCOL_CODE_H
#define TP3_TALLER_PROTOCOL_CODE_H

#include <cstdint>

enum CommandName: uint8_t { new_game, join_game };
enum JoinGameResponse: uint8_t { command_ok, game_is_full, non_existent_game };
enum EventType: uint8_t {
    object_moves, 
    object_switch_state, 
    player_wins, 
    player_loses, 
    player_dies,
    grab_rock,
    throw_rock
};

enum GameActionName : uint8_t {
    null_action, 
    quit_game, 
    move_left,
    move_right, 
    jump,
    stop_move, 
    open_blue_portal, 
    open_orange_portal,
    pin_tool_on,
    grab_it,
    throw_it,
    stop_grab,
    stop_throw
};

enum ThreadStatus{
    THREAD_STOP,
    THREAD_GO
};

#endif
