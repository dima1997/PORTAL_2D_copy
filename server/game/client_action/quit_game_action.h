//
// Created by franciscosicardi on 25/06/19.
//

#ifndef PORTAL_QUIT_GAME_ACTION_H
#define PORTAL_QUIT_GAME_ACTION_H


#include "client_action.h"

class QuitGameAction: public ClientAction {
private:
    void _execute(World &world) override;
public:
    explicit QuitGameAction(uint8_t playerId);
    ~QuitGameAction() override;
};


#endif //PORTAL_QUIT_GAME_ACTION_H
