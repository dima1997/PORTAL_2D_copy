#include "static_texture.h"

#include "big_texture.h"

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
StaticTexture::StaticTexture(BigTexture &bigTexture, Area areaSprite, 
                                Area areaMap) 
: bigTexture(bigTexture), areaSprite(std::move(areaSprite)), 
areaMap(std::move(areaMap)) {}


/*Destruye un textura estatica.*/
StaticTexture::~StaticTexture(){}

/*
Move Semantics
PRE: Recibe una doble referencia a otra textura estatica (StaticTexture &&).
POST: Contruye un nueva textura estatica por movimiento semantico.
*/
StaticTexture::StaticTexture(StaticTexture && otherStaticTexture) 
: bigTexture(otherStaticTexture.bigTexture) {
    this->areaSprite = std::move(otherStaticTexture.areaSprite);
    this->areaMap = std::move(otherStaticTexture.areaMap);
}

/*
Copy
PRE: Recibe una referencia constante a otra textura estatica 
(const StaticTexture &).
POST: Construye una nueva textura statica por copia.
*/
StaticTexture::StaticTexture(const StaticTexture & otherStaticTexture)
: bigTexture(otherStaticTexture.bigTexture) {
    this->areaSprite = otherStaticTexture.areaSprite;
    this->areaMap = otherStaticTexture.areaMap;
}

/* 
PRE: Recibe un factor de ajuste (float) que corresponde a la cantidad pixeles
por unidad de medida del area donde se ubica la textura (pixeles/unidad).
POST: Renderizala textura ajustandola.
Levanta SdlException en caso de error.
*/
void StaticTexture::render(float adjuster) {
    Area &src = this->areaSprite;
    Area dest = this->areaMap.adjust(adjuster);
    this->bigTexture.render(src, dest, NO_FLIP);
}
