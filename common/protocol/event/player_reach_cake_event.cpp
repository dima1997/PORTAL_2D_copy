#include "player_reach_cake_event.h"

#include "connector/connector.h"
#include "event.h"

#include <cstdint>

/*
PRE: Recibe el id del jugador que llego a la torta.
POST: Inicializa un evento de jugador que llego a torta.
*/
PlayerReachCakeEvent::PlayerReachCakeEvent(uint32_t id)
:   Event(player_reach_cake), id(id) {}

PlayerReachCakeEvent::~PlayerReachCakeEvent() = default;

/*
PRE: Recibe un conector (Connector &) conectado.
POST: Envia el evento: evento + id, a traves del connector.
*/
void PlayerReachCakeEvent::sendThrough(Connector & out) const {
    out << (uint8_t) this->eventType << this->id;
}

/*
PRE: Recibe un conector (Connector &) conectado.
POST: Recibe el evento (solo id), desde el connector.
*/
void PlayerReachCakeEvent::receiveFrom(Connector & in){
    in >> this->id;
}

/*Devuelve el id del jugador que llego a la torta.*/
uint32_t PlayerReachCakeEvent::get_id(){
    return this->id; 
}
