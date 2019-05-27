//
// Created by franciscosicardi on 26/05/19.
//

#ifndef PORTAL_PLAYER_DIES_EVENT_H
#define PORTAL_PLAYER_DIES_EVENT_H


#include "connector/connector.h"
#include "event.h"

class PlayerDiesEvent: public Event {
public:
    PlayerDiesEvent();
    ~PlayerDiesEvent() override;
    friend Connector &operator<<(Connector &out, const PlayerDiesEvent &c);
};


#endif //PORTAL_PLAYER_DIES_EVENT_H
