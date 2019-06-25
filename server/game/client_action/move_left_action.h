//
// Created by franciscosicardi on 25/06/19.
//

#ifndef PORTAL_MOVE_LEFT_ACTION_H
#define PORTAL_MOVE_LEFT_ACTION_H


#include "client_action.h"

class MoveLeftAction: ClientAction {
private:
    void _execute(World &world) override;
public:
    MoveLeftAction(GameActionName gameActionName, uint8_t playerId);
    ~MoveLeftAction() override;
};


#endif //PORTAL_MOVE_LEFT_ACTION_H
