#ifndef PLAYER_REACH_CAKES_EVENT_H
#define PLAYER_REACH_CAKES_EVENT_H

#include "connector/connector.h"
#include "event.h"

#include <cstdint>

class PlayerReachCakeEvent: public Event {
private:
    uint32_t id;
public:
    /*
    PRE: Recibe el id del jugador que llego a la torta.
    POST: Inicializa un evento de jugador que llego a torta.
    */
    explicit PlayerReachCakeEvent(uint32_t id);
    ~PlayerReachCakeEvent() override;

    /*
    PRE: Recibe un conector (Connector &) conectado.
    POST: Envia el evento: evento + id, a traves del connector.
    */
    virtual void sendThrough(Connector & out) const;

    /*
    PRE: Recibe un conector (Connector &) conectado.
    POST: Recibe el evento, desde el connector.
    */
    virtual void receiveFrom(Connector & in);

    /*Devuelve el id del jugador que llego a la torta*/
    uint32_t get_id();
};


#endif //PLAYER_REACH_CAKES_EVENT_H
