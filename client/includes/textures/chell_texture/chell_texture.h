#ifndef CHELL_TEXTURE_H
#define CHELL_TEXTURE_H

#include "move_sense.h"
#include "chell_sprite_strategy.h"
#include "../common_texture/area.h"
#include "../common_texture/big_texture.h"
#include "../common_texture/texture.h"

#include "../../mixer/sounds_path.h"

class ChellTexture : public Texture {
private:
    MoveSense moveSense;
    Area areaVision;
    bool alive;

    /*Actualiza el area de vision de Chell.*/
    void updateVisionArea();
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

    // Anulamos las copias
    ChellTexture(const ChellTexture & otherChellTextura) = delete;
    ChellTexture & operator=(const ChellTexture & otherChellTextura) = delete;

    /*
    PRE: Recibe una nueva coordenada (float) x,y .
    POST: Mueve la textura de Chell a la coordenada 
    indicada.
    */
    virtual void move_to(float x, float y) override;

    /*
    PRE: Recibe un factor de ajuster para redimensionar el area 
    de mapa que ocupa de Chell, a pixeles.
    POST: Renderiza la textura de Chell.
    */
    virtual void render(float adjuster, const Area & areaCamera) override;

    /*
    Alterna entre Chell viva y muerta.
    */
    virtual void switch_sprite();

    /*
    Devuelve el area de vision actual del 
    Chell en el mapa de juego.
    */
    virtual Area getVisionArea() override;

    /*
    PRE: Recibe las coordenadas (float) x,y 
    a donde apunta la textura
    POST: Apunta en la direccion indicada.
    */
    virtual void point_to(float x, float y) override;
};

#endif // CHELL_TEXTURE_H
