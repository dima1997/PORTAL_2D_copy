//
// Created by franciscosicardi on 25/06/19.
//

#ifndef PORTAL_THROW_RIGHT_ACTION_H
#define PORTAL_THROW_RIGHT_ACTION_H


#include "client_action.h"

class ThrowRightAction: ClientAction {
private:
    void _execute(World &world) override;
public:
    ThrowRightAction(GameActionName gameActionName, uint8_t playerId);
    ~ThrowRightAction() override;
};


#endif //PORTAL_THROW_RIGHT_ACTION_H
