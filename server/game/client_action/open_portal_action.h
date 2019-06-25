//
// Created by franciscosicardi on 25/06/19.
//

#ifndef PORTAL_OPEN_PORTAL_ACTION_H
#define PORTAL_OPEN_PORTAL_ACTION_H


#include "client_coord_action.h"

class OpenPortalAction: public ClientCoordAction {
private:
    void _execute(World &world) override;
    portal_color_t color;
public:
    OpenPortalAction(GameActionName gameActionName, uint8_t playerId, portal_color_t portalColor);
    ~OpenPortalAction() override;
};


#endif //PORTAL_OPEN_PORTAL_ACTION_H
