//
// Created by franciscosicardi on 25/06/19.
//

#ifndef STOP_MOVE_ACTION_H
#define STOP_MOVE_ACTION_H


#include "client_action.h"

class StopMoveAction: public ClientAction {
private:
    void _execute(World &world) override;
public:
    explicit StopMoveAction(uint8_t playerId);
    ~StopMoveAction() override;
};


#endif //STOP_MOVE_ACTION_H
