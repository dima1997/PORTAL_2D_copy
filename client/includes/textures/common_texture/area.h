#ifndef __AREA_H__
#define __AREA_H__

#include <tuple>

class Area {
private:
	float x, y;
	float width, height;
    
public:
    /*
    Construye un area de coordenadas y dimensiones cero.
    */
    Area();

    /*
    PRE: Recibe unas coordenadas x,y donde se 
    posicionara el area, y el ancho y largo 
    del mismo (todos float).
    POST: Inicializa un area.
    */
    Area(float x, float y, float width, float height);

    /*Destruye un area*/
    virtual ~Area();

    /*
    PRE: Recibe una doble referencia a otra area (Area &&).
    POST: Inicializa una nueva area por movimiento semantico.
    El area recibida queda en estado nulo.
    */
    Area(Area && otherArea);

    /*
    PRE: Recibe una doble referencia a otra area (Area &&).
    POST: Realiza una asignacion por movimiento semantico. 
    Devuelve una referencia al area actual.
    El area recibida queda en estado nulo.
    */
    Area & operator=(Area && otherArea);

    /*
    PRE: Recibe una referencia constante a otra area (const Area &).
    POST: Inicializa una nueva area por copia.
    */
    Area(const Area &otherArea);
    
    /*
    PRE: Recibe una referencia constante a otra area (const Area &).
    POST: Realiza una asignacion por copia. Devuelve una referencia al
    area actual
    */
    Area & operator=(const Area &otherArea);

    /*
    PRE: Recibe un factor de ajuste (<nueva unidad>/<unidad actual>)
    POST: Devuelve un nuevo area (Area) que ajusta la medidas 
    (coordenadas y dimensiones) del actual.
    */
    Area adjust(float adjuster) const;

    /*
    Devuelve un nuevo area con las coordenadas de su 
    actual esquina superior izquierda (relativo 
    al sistema de referencia usado).
    (Superior => y mas grande)
    (Izquieda => x mas chico)
    */
    Area from_center_to_top_left() const;

    /*
    PRE: Recibe las coordenadas (float) x,y del sistema de 
    referencia actual, que seran utilizadas como origen de 
    coordenadas del nuevo sistema de referencia, que tiene
    el eje de coordenadas Y, al reves del actual.
    POST: Devuelve un nuevo area (Area) con las coordenadas
    adaptadas al nuevo sistema de referencia.
    */
    Area to_y_axis_down_reference_system(float xOrigin, float yOrigin) const;


    /*Devuelve la coordenada (float) x del area*/
    float getX() const;

    /*Devuelve la coordenada (float) y del area*/
    float getY() const;

    /*Devuelve el ancho (float) del area*/
    float getWidth() const; 

    /*Devuelve la altura (float) del area*/
    float getHeight() const;
    
    /*
    Devuelve un vector de floats (std::vector<float>) con las coordenadas 
    extremas del area, suponiendo que la misma tiene sus coordenadas en el
    centro de la misma. 
    El orden de las coordenadas devueltas es el siguiente:
    xButton, xTop, yButton, yTop . 
    */
    std::tuple<float,float,float,float> getExtremeCoords() const;

    /*
    PRE: Recibe una referencia constante a otra area (const Area &).
    POST: Devuele true, si ambas areas se intersecan en algun punto;
    false en caso contrario.
    */
    bool isIntersectedBy(const Area & otherArea) const;
    
    /*
    PRE: Recibe una nueva coordanada (float) x.
    POST: Cambia el valor de coordenada x del area 
    por el recibido.
    */
    void setX(float x);
    
    /*
    PRE: Recibe una nueva coordanada (float) y.
    POST: Cambia el valor de coordenada y del area 
    por el recibido.
    */
    void setY(float y);

    /*
    PRE: Recibe un nuevo ancho (float).
    POST: Cambia el valor de anche del area 
    por el recibido.
    */
    void setWidth(float width);

    /*
    PRE: Recibe un nuevoa alto (float) y.
    POST: Cambia el valor de alto del area 
    por el recibido.
    */
    void setHeight(float height);
};

#endif
