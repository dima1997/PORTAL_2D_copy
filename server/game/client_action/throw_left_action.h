//
// Created by franciscosicardi on 25/06/19.
//

#ifndef PORTAL_THROW_LEFT_ACTION_H
#define PORTAL_THROW_LEFT_ACTION_H


#include "client_action.h"

class ThrowLeftAction: ClientAction {
private:
    void _execute(World &world) override;
public:
    ThrowLeftAction(GameActionName gameActionName, uint8_t playerId);
    ~ThrowLeftAction() override;
};


#endif //PORTAL_THROW_LEFT_ACTION_H
