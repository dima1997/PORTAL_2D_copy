#ifndef SOUNDS_PATH_H
#define SOUNDS_PATH_H

#include <map>
#include <string>

enum SOUND_NAME {
    SOUND_DYING,
    SOUND_JUMP,
    SOUND_PORTAL_SHOOT,
    SOUND_RADIO_SONG
};

const std::map<SOUND_NAME, std::string> SOUNDS_PATH({
    std::make_pair<SOUND_NAME, std::string>(SOUND_DYING, "dying.wav"),
    std::make_pair<SOUND_NAME, std::string>(SOUND_JUMP, "jump.wav"),
    std::make_pair<SOUND_NAME, std::string>(SOUND_PORTAL_SHOOT, "portal_shoot.wav"),
    std::make_pair<SOUND_NAME, std::string>(SOUND_RADIO_SONG, "portal_radio.wav")
});

#endif // SOUNDS_PATH_H
