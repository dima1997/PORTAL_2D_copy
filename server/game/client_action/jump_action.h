//
// Created by franciscosicardi on 25/06/19.
//

#ifndef JUMP_ACTION_H
#define JUMP_ACTION_H


#include "client_action.h"

class JumpAction: ClientAction {
private:
    void _execute(World &world) override;
public:
    JumpAction(GameActionName gameActionName, uint8_t playerId);
    ~JumpAction() override;
};


#endif //JUMP_ACTION_H
