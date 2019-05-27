//
// Created by franciscosicardi on 12/05/19.
//

#include <portal_exception.h>
#include <protocol/event/event.h>
#include <protocol/event/object_moves_event.h>
#include "game.h"

Game::Game(Connector &connector, uint8_t game_id, uint8_t player_id):
            connector(std::move(connector)), gameId(game_id), playerId(player_id) {}

void Game::operator()() {
    Event *event;
    bool cont = true;
    while (cont) {
        uint8_t eventType;
        connector >> eventType;
        switch ((EventType) eventType) {
            case object_moves:
                event = new ObjectMovesEvent();
                connector >> *(ObjectMovesEvent *) event;
                printf("x: %4.2f, y: %4.2f\n", ((ObjectMovesEvent *)event)->getX(), ((ObjectMovesEvent *)event)->getY());
                connector << (uint8_t) move_left;
                break;
            case player_dies:
            case player_wins:
                cont = false;
                break;
            default:
                throw PortalException("Unknown action");

        }
    }
}
