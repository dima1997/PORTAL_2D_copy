#ifndef OBJECT_SWITCH_EVENT_H
#define OBJECT_SWITCH_EVENT_H

#include "event.h"

#include <connector/connector.h>

#include <cstdint>

class ObjectSwitchEvent : public Event{
private: 
    uint32_t idObject;
public:
    /*
    PRE Recibe el id (uint32_t) del objeto donde realizar el switch.
    POST: Inicializa un evento de swtich de un objeto del juego. 
    */
    explicit ObjectSwitchEvent(uint32_t idObject);

    /*
    Inicializa un evento de swtich de un objeto del juego,
    con id de objecto nulo. 
    */
    ObjectSwitchEvent();

    /*Destruye un eventor switcher de objectos.*/
    ~ObjectSwitchEvent();
    /*
    PRE: Recibe un conector (Connector &) conectado.
    POST: Recibe el id del objeto en donde realizar el
    switch, desde el conector. 
    */
    void receiveFrom(Connector & in);
    /*
    PRE: Recibe un conector (Connector &) conectado.
    POST: Envia el tipo de evento actual, seguido del
    id del objecto, a traves del connector.
    */
    void sendThrough(Connector & out) const;

    /*Devuelve el id del objeto donde realizar el switch.*/
    uint32_t getObjectId() const;
    };

#endif // OBJECT_SWITCH_EVENT_H
