#ifndef TEXTURE_SWITCH_CHANGE_H
#define TEXTURE_SWITCH_CHANGE_H

#include "../../../includes/textures/common_texture/texture_change.h"

#include "../../../includes/window/window.h"

#include <protocol/event/object_switch_event.h>

class TextureSwitchChange : public TextureChange {
public:
    /*
    PRE: Recibe un evento de swtich en objeto 
    (const ObjectSwitchEvent &).
    POST: Inicializa un cambio de tipo switch
    en textura.
    */
    TextureSwitchChange(const ObjectSwitchEvent & ObjectSwitchEvent);
    
    /*Destruye el cambio de tipo switch en textura.*/
    virtual ~TextureSwitchChange();

    /*
    PRE: Recibe una referncia a una ventana que 
    contenga la textura de id del cambio actual.
    POST: Realiza el cambio de tipo switch, en
    la textura correspondiente, a traves de la 
    ventana.
    */
    virtual void change(Window & window);
};

#endif // TEXTURE_SWITCH_CHANGE_H
