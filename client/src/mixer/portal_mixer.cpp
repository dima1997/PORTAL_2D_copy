#include "../../includes/mixer/portal_mixer.h"

#include "../../includes/mixer/mixer.h"
#include "../../includes/mixer/sounds_path.h"

#include <vector>
#include <string>

/*
Inicializa un creador de sonidos 
del juego portal.
*/
PortalMixer::PortalMixer(){}

/*
Destruye el creador del 
portal mixer.
*/
PortalMixer::~PortalMixer() = default;

/*
Devuelve un mixer con todos los sonidos que el juego 
portal reproduce en algun momento.
*/
Mixer PortalMixer::create_mixer(){
    std::vector<std::string> pathsChunck;
    pathsChunck.push_back(SOUNDS_PATH.at(SOUND_DYING));
    pathsChunck.push_back(SOUNDS_PATH.at(SOUND_JUMP));
    pathsChunck.push_back(SOUNDS_PATH.at(SOUND_PORTAL_SHOOT));
    const std::string & pathMusic = SOUNDS_PATH.at(SOUND_RADIO_SONG);
    return std::move(Mixer(pathMusic, pathsChunck));
} 
