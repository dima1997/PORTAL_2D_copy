//
// Created by franciscosicardi on 25/06/19.
//

#ifndef PORTAL_CLIENT_COORD_ACTION_H
#define PORTAL_CLIENT_COORD_ACTION_H


#include <connector/connector.h>
#include <protocol/protocol_code.h>
#include "client_action.h"

class ClientCoordAction: public ClientAction {
protected:
    float32 xMap;
    float32 yMap;
public:
    explicit ClientCoordAction(uint8_t playerId);
    ~ClientCoordAction() override;
    Connector &receiveFrom(Connector &out) override;



};


#endif //PORTAL_CLIENT_COORD_ACTION_H
