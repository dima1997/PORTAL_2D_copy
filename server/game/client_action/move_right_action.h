//
// Created by franciscosicardi on 25/06/19.
//

#ifndef PORTAL_MOVE_RIGHT_ACTION_H
#define PORTAL_MOVE_RIGHT_ACTION_H


#include "client_action.h"

class MoveRightAction: ClientAction {
private:
    void _execute(World &world) override;
public:
    MoveRightAction(GameActionName gameActionName, uint8_t playerId);
    ~MoveRightAction() override;
};


#endif //PORTAL_MOVE_RICHT_ACTION_H
