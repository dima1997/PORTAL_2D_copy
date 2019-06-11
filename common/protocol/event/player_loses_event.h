#ifndef PLAYER_LOSES_EVENT_H
#define PLAYER_LOSES_EVENT_H

#include "event.h"

class PlayerLosesEvent : public Event {
public:
    PlayerLosesEvent();
    ~PlayerLosesEvent() override;
};

#endif // PLAYER_LOSES_EVENT_H
