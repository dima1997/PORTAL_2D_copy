#include "static_texture.h"

#include "big_texture.h"

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
StaticTexture::StaticTexture(BigTexture &bigTexture,
                                unsigned int xImage, unsigned int yImage, 
                                unsigned int widthImage, unsigned int heightImage, 
                                unsigned int xPos, unsigned int yPos) 
: bigTexture(bigTexture), xImage(xImage), yImage(yImage), 
widthImage(widthImage), heightImage(heightImage), 
xPos(xPos), yPos(yPos) {}

/*Destruye un textura estatica.*/
StaticTexture::~StaticTexture(){}

/*
Move Semantics
PRE: Recibe una doble referencia a otra textura estatica (StaticTexture &&).
POST: Contruye un nueva textura estatica por movimiento semantico.
*/
StaticTexture::StaticTexture(StaticTexture && otherStaticTexture) 
: bigTexture(otherStaticTexture.bigTexture) {
    this->xImage = otherStaticTexture.xImage;
    this->yImage = otherStaticTexture.yImage;
    this->widthImage = otherStaticTexture.widthImage;
    this->heightImage = otherStaticTexture.heightImage;
    this->xPos = otherStaticTexture.xPos;
    this->yPos = otherStaticTexture.yPos;
    otherStaticTexture.xImage = 0;
    otherStaticTexture.yImage = 0;
    otherStaticTexture.widthImage = 0;
    otherStaticTexture.heightImage = 0;
    otherStaticTexture.xPos = 0;
    otherStaticTexture.yPos = 0;
}

/*
Copy
PRE: Recibe una referencia constante a otra textura estatica 
(const StaticTexture &).
POST: Construye una nueva textura statica por copia.
*/
StaticTexture::StaticTexture(const StaticTexture & otherStaticTexture)
: bigTexture(otherStaticTexture.bigTexture) {
    this->xImage = otherStaticTexture.xImage;
    this->yImage = otherStaticTexture.yImage;
    this->widthImage = otherStaticTexture.widthImage;
    this->heightImage = otherStaticTexture.heightImage;
    this->xPos = otherStaticTexture.xPos;
    this->yPos = otherStaticTexture.yPos;
}


/*
PRE: Recibe el ancho y alto de la ventana donde se renderiza la textura 
estatica actual (unsigned int), y la escalas maximas (float positivos) 
en ancho y alto con respecto a las dimensiones de la imagen a renderizar:
    widthWindow >= scaleWidth * <static texture width>
    heightWindow >= scaleHeight * <static texture height> 
POST: Renderizala textura en la ventana
*/
void StaticTexture::render(unsigned int widthWindow, unsigned int heightWindow, 
                            float scaleWidth, float scaleHeight) {
    Area src(this->xImage, this->yImage, this->widthImage, this->heightImage);
    float adjusterWidth = (scaleWidth * widthWindow)/this->widthImage;
    float adjusterHeight = (scaleHeight * heightWindow)/this->heightImage;
    float adjuster = 1;
    if (adjusterWidth < adjusterHeight){
        adjuster = adjusterWidth;
    } else {
        adjuster = adjusterHeight;
    }
    unsigned int widthImageRect = this->widthImage * adjuster;
    unsigned int heightImageRect = this->heightImage * adjuster;
    Area dest(this->xPos, this->yPos, widthImageRect, heightImageRect);
    this->bigTexture.render(src, dest);
}