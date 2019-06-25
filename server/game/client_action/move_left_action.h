//
// Created by franciscosicardi on 25/06/19.
//

#ifndef PORTAL_MOVE_LEFT_ACTION_H
#define PORTAL_MOVE_LEFT_ACTION_H


#include "client_action.h"

class MoveLeftAction: public ClientAction {
private:
    void _execute(World &world) override;
public:
    explicit MoveLeftAction(uint8_t playerId);
    ~MoveLeftAction() override;
};


#endif //PORTAL_MOVE_LEFT_ACTION_H
