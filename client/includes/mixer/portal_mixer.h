#ifndef PORTAL_MIXER_H
#define PORTAL_MIXER_H

#include "mixer.h"

class PortalMixer {
public:
    /*
    Inicializa un creador de sonidos 
    del juego portal.
    */
    PortalMixer();

    /*
    Destruye el creador del 
    portal mixer.
    */
    ~PortalMixer();

    /*
    Devuelve un mixer con todos los 
    sonidos que el juego portal 
    reproduce en algun momento.
    */
    Mixer create_mixer();
};

#endif // PORTAL_MIXER_H  
