#ifndef STATIC_TEXTURE_H
#define STATIC_TEXTURE_H

#include "big_texture.h"

class StaticTexture {
private:
    BigTexture & bigTexture;
    unsigned int xImage;
    unsigned int yImage;
    unsigned int widthImage;
    unsigned int heightImage;
    unsigned int xPos;
    unsigned int yPos;
public:
    /*
    PRE: Recibe:
        Una gran textura (BigTexture &).
        La coordenada x,y en pixeles (unsigned int) de la esquina superior 
        izquierda del extracto rectangular de la gran textura que se va a utilizar.
        El ancho y alto en pixeles (unsigned int) del extracto rectangular.
        Y la posicion x,y en metros (unsigned int) de la esquina superior 
        izquierda del extracto rectangular en el mapa de juego.
    POST: Inicializa un textura estatica.
    */
    StaticTexture(BigTexture &bigTexture, 
                    unsigned int xImage, unsigned int yImage, 
                    unsigned int widthImage, unsigned int heightImage, 
                    unsigned int xPos, unsigned int yPos);

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
    PRE: Recibe el ancho y largo de la ventana donde ser renderiza (unsigned int), y
    la escala de que porcentaje de la ventana deberia ocupar .
    POST: Renderizala textura 
    */
    virtual void render(unsigned int widthScreen, unsigned int heightScreen, 
                        float scaleWidth = 1, float scaleHeight = 1);
};

#endif // STATIC_TEXTURE_H