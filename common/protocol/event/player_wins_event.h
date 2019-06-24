//
// Created by franciscosicardi on 26/05/19.
//

#ifndef PORTAL_PLAYER_WINS_EVENT_H
#define PORTAL_PLAYER_WINS_EVENT_H

#include "event.h"

class PlayerWinsEvent: public Event {
public:
    PlayerWinsEvent();
    virtual ~PlayerWinsEvent() override;
};


#endif //PORTAL_PLAYER_WINS_EVENT_H
