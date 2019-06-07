#ifndef DYNAMIC_SPRITE_H
#define DYNAMIC_SPRITE_H

#include "area.h"

#include <vector>

class DynamicSprite {
private:
    std::vector<std::pair<int, int>> spritesCoordTape;
    int width;
    int height;
    int index;
public:
    /*
    PRE: Recibe un vector de coordenadas x,y (std::vector<std::pair<int, int>>) de
    las esquinas superior izquierda de cada sprite a utilizar, en el orden a ser
    alternados; el ancho y alto (int) de cada sprite del vector.
    (Se supone que todos los sprites en el vector recibido tienen las misma 
    dimension, en pixeles).
    POST: Inicializa un sprite dinamico. 
    */
    DynamicSprite(std::vector<std::pair<int, int>> spritesCoordTape,
                                 int width, int height);
    /*Destruye el sprite dinamico.*/
    virtual ~DynamicSprite();

    /*
    Devuelve un area (Area) con las coordenadas y dimension del proximo a sprite a 
    ser usado.
    */
    Area getNextArea();

    /*
    Devuelve true, si el sprite actual es el ultimo 
    sprite de la tira de sprites que los constituyen; 
    false en caso contrario.
    */
    bool is_last_sprite();
    
    /*Reinicia el ciclo de sprites al sprite inicial.*/
    void restart();
};

#endif // DYNAMIC_SPRITE_H