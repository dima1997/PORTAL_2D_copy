//
// Created by franciscosicardi on 10/06/19.
//

#ifndef PORTAL_GRAB_ROCK_EVENT_H
#define PORTAL_GRAB_ROCK_EVENT_H


#include "event.h"

class GrabRockEvent: public Event {
private:
    uint32_t chellId;
    uint32_t rockId;
public:
    GrabRockEvent(uint32_t chellId, uint32_t rockId);
    ~GrabRockEvent() override;
    uint32_t getChellId() const;
    uint32_t getRockId() const;
    void receiveFrom(Connector & in) override;
    void sendThrough(Connector & out) const override;
};


#endif //PORTAL_GRAB_ROCK_EVENT_H
