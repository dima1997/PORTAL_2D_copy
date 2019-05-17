#ifndef __AREA_H__
#define __AREA_H__

class Area {
private:
	int x, y;
	int width, height;
public:
    /*
    Construye un area de coordenadas y dimensiones cero.
    */
    Area();

    /*
    PRE: Recibe unas coordenadas x,y donde se 
    posicionara el area, y el ancho y largo 
    del mismo (todo int).
    POST: Inicializa un area.
    */
    Area(int x, int y, int width, int height);

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

    /*Devuelve la coordenada (int) x del area*/
    int getX() const;

    /*Devuelve la coordenada (int) y del area*/
    int getY() const;

    /*Devuelve el ancho (int) del area*/
    int getWidth() const; 

    /*Devuelve la altura (int) del area*/
    int getHeight() const;
};

#endif
