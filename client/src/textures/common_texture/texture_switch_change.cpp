#include "../../../includes/textures/common_texture/texture_switch_change.h"

#include "../../../includes/textures/common_texture/texture_change.h"
#include "../../../includes/window/window.h"

#include <protocol/event/object_switch_event.h>

/*
PRE: Recibe un evento de swtich en objeto 
(const ObjectSwitchEvent &).
POST: Inicializa un cambio de tipo switch
en textura.
*/
TextureSwitchChange::TextureSwitchChange
(const ObjectSwitchEvent & objectSwitchEvent)
:   TextureChange(objectSwitchEvent.getObjectId()) {}

/*Destruye el cambio de tipo switch en textura.*/
TextureSwitchChange::~TextureSwitchChange() = default;

/*
PRE: Recibe una referncia a una ventana que 
contenga la textura de id del cambio actual.
POST: Realiza el cambio de tipo switch, en
la textura correspondiente, a traves de la 
ventana.
*/
void TextureSwitchChange::change(Window & window){
    window.switch_texture(this->id);
}
