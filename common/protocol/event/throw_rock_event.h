//
// Created by franciscosicardi on 10/06/19.
//

#ifndef PORTAL_THROW_ROCK_EVENT_H
#define PORTAL_THROW_ROCK_EVENT_H


#include "event.h"

class ThrowRockEvent: public Event {
private:
    uint32_t rockId;
public:
    explicit ThrowRockEvent(uint32_t rockId);
    ~ThrowRockEvent() override;
    uint32_t getRockId() const;
    void receiveFrom(Connector & in) override;
    void sendThrough(Connector & out) const override;
};


#endif //PORTAL_THROW_ROCK_EVENT_H
