//
// Created by franciscosicardi on 26/05/19.
//

#include "event.h"
#include "game_starts_event.h"

GameStartsEvent::GameStartsEvent(): Event(game_starts) {}

GameStartsEvent::~GameStartsEvent() = default;
