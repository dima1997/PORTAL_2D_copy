//
// Created by franciscosicardi on 26/05/19.
//

#ifndef PORTAL_PLAYER_WINS_EVENT_H
#define PORTAL_PLAYER_WINS_EVENT_H


#include "connector/connector.h"
#include "event.h"

class PlayerWinsEvent: public Event {
public:
    PlayerWinsEvent();
    ~PlayerWinsEvent() override;
    friend Connector &operator<<(Connector &out, const PlayerWinsEvent &c);
};


#endif //PORTAL_PLAYER_WINS_EVENT_H
