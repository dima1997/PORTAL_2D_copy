//
// Created by franciscosicardi on 25/06/19.
//

#ifndef PORTAL_PIN_TOOL_ACTION_H
#define PORTAL_PIN_TOOL_ACTION_H


#include "client_coord_action.h"

class PinToolAction: public ClientCoordAction {
private:
    void _execute(World &world) override;
public:
    PinToolAction(GameActionName gameActionName, uint8_t playerId);
    ~PinToolAction() override;
};


#endif //PORTAL_PIN_TOOL_ACTION_H
