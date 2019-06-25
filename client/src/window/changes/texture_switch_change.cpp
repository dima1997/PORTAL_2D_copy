#include "../../../includes/window/changes/texture_switch_change.h"

#include "../../../includes/window/window.h"

#include <protocol/event/object_switch_event.h>
#include <connector/connector.h>

/*
PRE: Recibe un connector por donde se recibira a 
continuacion un ObjectSwitchEvent
POST: Inicializa un cambio de tipo switch
en textura.
*/
TextureSwitchChange::TextureSwitchChange(Connector & connector){
    ObjectSwitchEvent event;
    connector >> event;
    this->id = event.getObjectId();
}

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
