//
// Created by franciscosicardi on 26/05/19.
//

#ifndef PORTAL_PLAYER_DIES_EVENT_H
#define PORTAL_PLAYER_DIES_EVENT_H


#include "connector/connector.h"
#include "event.h"

class PlayerDiesEvent: public Event {
private:
    uint32_t id;
public:
    explicit PlayerDiesEvent(uint32_t id);
    ~PlayerDiesEvent() override;

    /*
    PRE: Recibe un conector (Connector &) conectado.
    POST: Envia el evento: evento + id, a traves del connector.
    */
    virtual void sendThrough(Connector & out) const;
    friend Connector &operator<<(Connector &out, const PlayerDiesEvent &c);
};


#endif //PORTAL_PLAYER_DIES_EVENT_H
