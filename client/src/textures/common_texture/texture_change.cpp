#include "../../../includes/textures/common_texture/texture_change.h"

#include "../../../includes/window/window.h"

#include <cstdint>

/*
PRE: Recibe el id de la textura donde se 
realizar el cambio.
POST: Inicializa un cambio en textura nulo.
*/
TextureChange::TextureChange(uint32_t idTexture)
: idTexture(idTexture) {}

/*Destruye el cambio en textura.*/
TextureChange::~TextureChange() = default;

/*
PRE: Recibe una ventana donde se encuentre la 
textura con el id correspondiente a este cambio.
POST: Realiza un cambio nulo en la ventana.
*/
void TextureChange::change(Window & window) {}
