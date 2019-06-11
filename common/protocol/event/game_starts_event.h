//
// Created by franciscosicardi on 26/05/19.
//

#ifndef PORTAL_GAME_STARTS_EVENT_H
#define PORTAL_GAME_STARTS_EVENT_H

#include "event.h"

class GameStartsEvent: public Event {
public:
    GameStartsEvent();
    ~GameStartsEvent() override;
};


#endif //PORTAL_GAME_STARTS_EVENT_H
