//
// Created by franciscosicardi on 09/05/19.
//

#ifndef TP3_TALLER_PROTOCOL_CODE_H
#define TP3_TALLER_PROTOCOL_CODE_H

#include <cstdint>

enum CommandName: uint8_t { new_game, join_game };
enum JoinGameResponse: uint8_t { command_ok, game_is_full, non_existent_game };
enum EventType: uint8_t {object_moves, player_wins, player_dies, object_switch_state};

enum GameActionName : uint8_t {null_action, move_left, move_right};

#endif
