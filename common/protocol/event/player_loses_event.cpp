#include "player_loses_event.h"

#include "event.h"

PlayerLosesEvent::PlayerLosesEvent() 
:   Event(player_loses) {}

PlayerLosesEvent::~PlayerLosesEvent() = default;
