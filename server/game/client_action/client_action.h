//
// Created by franciscosicardi on 25/06/19.
//

#ifndef PORTAL_CLIENTACTION_H
#define PORTAL_CLIENTACTION_H


#include <protocol/protocol_code.h>
#include <connector/connector.h>
#include "../model/chell.h"
#include "../world.h"

class ClientAction {
private:
    GameActionName gameActionName;
    virtual void _execute(World &world) = 0;
protected:
    uint32_t playerId;
public:
    ClientAction(GameActionName gameActionName, uint8_t playerId);
    ClientAction(const ClientAction &clientAction);
    virtual ~ClientAction();
    virtual Connector &receiveFrom(Connector &out);
    friend Connector &operator>>(Connector &out, ClientAction &action);
    void execute(World &world);
};


#endif //PORTAL_CLIENTACTION_H
