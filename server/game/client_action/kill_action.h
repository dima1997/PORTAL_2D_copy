//
// Created by franciscosicardi on 25/06/19.
//

#ifndef KILL_ACTION_H
#define KILL_ACTION_H


#include "client_action.h"

class KillAction: ClientAction {
private:
    void _execute(World &world) override;
public:
    KillAction(GameActionName gameActionName, uint8_t playerId);
    ~KillAction() override;
};


#endif //KILL_ACTION_H
