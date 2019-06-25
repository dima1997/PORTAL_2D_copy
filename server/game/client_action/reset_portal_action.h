//
// Created by franciscosicardi on 25/06/19.
//

#ifndef PORTAL_RESET_ACTION_H
#define PORTAL_RESET_ACTION_H // |


#include "client_action.h"

class ResetPortalAction: public ClientAction {
private:
    void _execute(World &world) override;
public:
    explicit ResetPortalAction(uint8_t playerId);
    ~ResetPortalAction() override;
};


#endif //PORTAL_RESET_ACTION_H
