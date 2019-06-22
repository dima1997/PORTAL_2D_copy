//
// Created by franciscosicardi on 21/05/19.
//

#ifndef PORTAL_OBJECT_MOVES_EVENT_H
#define PORTAL_OBJECT_MOVES_EVENT_H


#include "event.h"
#include "connector/connector.h"

class ObjectMovesEvent: public Event {
protected:
    uint32_t objectId;
    float xPos;
    float yPos;
public:
    ObjectMovesEvent(int objectId, float xPos, float yPos);
    ObjectMovesEvent(
        int objectId, 
        float xPos, 
        float yPos, 
        EventType eventType
    );
    ObjectMovesEvent();
    ~ObjectMovesEvent() override;
    uint32_t getId() const ;
    float getX() const;
    float getY() const;
    /*
    PRE: Recibe un conector (Connector &) conectado.
    POST: Recibe el evento, desde el connector.
    */
    virtual void receiveFrom(Connector & in) override;
    /*
    PRE: Recibe un conector (Connector &) conectado.
    POST: Envia el evento, a traves del connector.
    */
    virtual void sendThrough(Connector & out) const override;
};


#endif //PORTAL_OBJECT_MOVES_EVENT_H
