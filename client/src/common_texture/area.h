#ifndef __AREA_H__
#define __AREA_H__

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
    ~Area();

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
    POST: Devuelve un nuevo area (Area) que ajusta la medidas del actual.
    */
    Area adjust(float adjuster);

    /*Devuelve la coordenada (float) x del area*/
    float getX() const;

    /*Devuelve la coordenada (float) y del area*/
    float getY() const;

    /*Devuelve el ancho (float) del area*/
    float getWidth() const; 

    /*Devuelve la altura (float) del area*/
    float getHeight() const;
    
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
};

#endif
