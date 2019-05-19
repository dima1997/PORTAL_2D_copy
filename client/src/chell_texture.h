#ifndef CHELL_TEXTURE_H
#define CHELL_TEXTURE_H

#include "big_texture.h"
#include "chell_sprite_state.h"
#include "move_sense.h"
#include "area.h"
#include "renderizable.h"
#include "movable.h"

class ChellTexture : public Renderizable, public Movable {
private:
    BigTexture &bigTexture;
    MoveSense moveSense;
    ChellSpriteState spriteState;
    Area areaMap;

public:
    /*
    PRE: Recibe :
        Una referencia a la gran textura con todos los sprites de Chell.
        El area con las coordenadas y dimensiones de la localizacion de 
        Chell en el mapa de juego.
    POST: Inicializa una textura dinamica de Chell.
    */
    ChellTexture(BigTexture &bigTextureChell, Area areaMap);

    /*Destruye la textura dinamica de Chell.*/
    ~ChellTexture();

    /*
    PRE: Recibe una nueva coordenada (float) x,y .
    POST: Mueve la textura de Chell a la coordenada 
    indicada.
    */
    void move_to(float x, float y);

    /*
    PRE: Recibe un factor de ajuster para redimensionar el area 
    de mapa que ocupa de Chell, a pixeles.
    POST: Renderiza la textura de Chell.
    */
    void render(float adjuster);
};

#endif // CHELL_TEXTURE_H
