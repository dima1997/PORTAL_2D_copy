//
// Created by franciscosicardi on 26/05/19.
//

#ifndef PORTAL_GAME_ENDS_EVENT_H
#define PORTAL_GAME_ENDS_EVENT_H

#include "event.h"

class GameEndsEvent: public Event {
public:
    GameEndsEvent();
    ~GameEndsEvent() override;
};


#endif //PORTAL_GAME_ENDS_EVENT_H
