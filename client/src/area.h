#ifndef __AREA_H__
#define __AREA_H__

class Area {
private:
	int x, y;
	int width, height;
public:
    /*
    PRE: Recibe unas coordenadas x,y donde se 
    posicionara el area, y el ancho y largo 
    del mismo (todo int).
    POST: Inicializa un area.
    */
    Area(int x, int y, int width, int height);

    /*Destruye un area*/
    ~Area();

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
