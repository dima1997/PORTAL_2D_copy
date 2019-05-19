#ifndef STATIC_TEXTURE_H
#define STATIC_TEXTURE_H

#include "renderizable.h"
#include "big_texture.h"

class StaticTexture : public Renderizable {
private:
    BigTexture & bigTexture;
    Area areaSprite;
    Area areaMap;
public:
    /*
    PRE: Recibe:
        Una gran textura (BigTexture &).
        Un area (Area) con las coordenadas y dimensiones del sprite a usar de 
        la gran textura (en pixeles).
        Un area (Area) con las coordenadas y dimensiones del objeto que 
        representa la textura en el mapa de juego (en metros).
    POST: Inicializa un textura estatica.
    Levanta SdlException en caso de error.
    */
    StaticTexture(BigTexture &bigTexture, Area areaSprite, Area areaMap);

    /*Destruye un textura estatica.*/
    virtual ~StaticTexture();
    
    /*
    Move Semantics
    PRE: Recibe una doble referencia a otra textura estatica (StaticTexture &&).
    POST: Contruye un nueva textura estatica por movimiento semantico.
    */
    StaticTexture(StaticTexture && otherStaticTexture); 

    /*
    Copy.
    PRE: Recibe una referencia constante a otra textura estatica 
    (const StaticTexture &).
    POST: Construye una nueva textura statica por copia.
    */
    StaticTexture(const StaticTexture & otherStaticTexture);

    /*
    No permite asignaciones.
    */
    StaticTexture & operator=(StaticTexture && otherStaticTexture) = delete;
    StaticTexture & operator=(const StaticTexture & otherStaticTexture) = delete;

    /* 
    PRE: Recibe un factor de ajuste (float) que corresponde a la cantidad pixeles
    por unidad de medida del area donde se ubica la textura (pixeles/unidad).
    POST: Renderizala textura ajustandola.
    Levanta SdlException en caso de error.
    */
    virtual void render(float adjuster);
};

#endif // STATIC_TEXTURE_H