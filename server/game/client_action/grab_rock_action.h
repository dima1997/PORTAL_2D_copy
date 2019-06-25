//
// Created by franciscosicardi on 25/06/19.
//

#ifndef GRAB_ROCK_ACTION_H
#define GRAB_ROCK_ACTION_H


#include "client_action.h"

class GrabRockAction: public ClientAction {
private:
    void _execute(World &world) override;
public:
    explicit GrabRockAction(uint8_t playerId);
    ~GrabRockAction() override;
};


#endif //GRAB_ROCK_ACTION_H
