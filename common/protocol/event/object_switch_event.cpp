#include "object_switch_event.h"

#include <connector/connector.h>

#include <cstdint>
/*
PRE Recibe el id (uint32_t) del objeto donde realizar el switch.
POST: Inicializa un evento de swtich de un objeto del juego. 
*/
ObjectSwitchEvent::ObjectSwitchEvent(uint32_t idObject)
:   Event(object_switch_state), idObject(idObject) {}

/*
Inicializa un evento de swtich de un objeto del juego,
con id de objecto nulo. 
*/
ObjectSwitchEvent::ObjectSwitchEvent()
:   Event(object_switch_state), idObject(-1) {}

/*Destruye un eventor switcher de objectos.*/
ObjectSwitchEvent::~ObjectSwitchEvent() = default;
/*
PRE: Recibe un conector (Connector &) conectado.
POST: Recibe el id del objeto en donde realizar el
switch, desde el conector. 
*/
void ObjectSwitchEvent::receiveFrom(Connector & in){
    in >> this->idObject;
}
/*
PRE: Recibe un conector (Connector &) conectado.
POST: Envia el tipo de evento actual, seguido del
id del objecto, a traves del connector.
*/
void ObjectSwitchEvent::sendThrough(Connector & out) const{
    uint8_t eventTypeExplicit = (uint8_t) this->eventType;
    out << eventTypeExplicit;
    out << (uint32_t) this->idObject; 
}  

/*Devuelve el id del objeto donde realizar el switch.*/
uint32_t ObjectSwitchEvent::getObjectId() const{
    return this->idObject;
}
