//
// Created by franciscosicardi on 25/06/19.
//

#ifndef PORTAL_THROW_RIGHT_ACTION_H
#define PORTAL_THROW_RIGHT_ACTION_H


#include "client_action.h"

class ThrowRightAction: public ClientAction {
private:
    void _execute(World &world) override;
public:
    explicit ThrowRightAction(uint8_t playerId);
    ~ThrowRightAction() override;
};


#endif //PORTAL_THROW_RIGHT_ACTION_H
