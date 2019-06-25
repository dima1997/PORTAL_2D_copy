#ifndef TEXTURE_SWITCH_CHANGE_H
#define TEXTURE_SWITCH_CHANGE_H

#include "change.h"

class Window;
class Connector;

class TextureSwitchChange : public Change {
private:
    uint32_t id;
public:
    /*
    PRE: Recibe un connector por donde se recibira a 
    continuacion un ObjectSwitchEvent.
    POST: Inicializa el cambio.
    */
    TextureSwitchChange(Connector & connector);

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
