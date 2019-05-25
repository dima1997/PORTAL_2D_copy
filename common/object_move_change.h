#ifndef OBJECT_MOVE_CHANGE_H
#define OBJECT_MOVE_CHANGE_H

#include <cstdint>

class ObjectMoveChange {
private:
    uint32_t idGameObject;
    float newX;
    float newY;
    
public:
    /*
    PRE: Recibe el id de un objeto de juego donde se quiera 
    realizar el cambio; y las nuevas coordenadas (float) x,y
    del objeto antes mencionado.
    POST: inicializa un cambio de ubicacion en un objeto del
    juego.
    */
    ObjectMoveChange(uint32_t idGameObject, float newX, float newY);

    /*Destruye el cambio de un objeto del juego.*/
    ~ObjectMoveChange();

    /*
    Contructor por copia.
    PRE: Recibe una referencia constante a otro cambio de ubicacion 
    de un objeto del juego (const ObjectMoveChange &).
    POST: Inicializa un nuevo cambio de ubicacion de un objeto del 
    juego, por copia.
    */
    ObjectMoveChange(const ObjectMoveChange & other);

    /*
    Asignacion por copia.
    PRE: Recibe una referencia constante a otro cambio de ubicacion 
    de un objeto del juego (const ObjectMoveChange &).
    POST: Asigna los atributos del cambio de ubicacion de un objeto del 
    juego recibido, al actual.
    Devuelve una referencia al cambio actual (ObjectMoveChange &).
    */
    ObjectMoveChange & operator=(const ObjectMoveChange & other);

    /*
    Devuelve el id (uint32_t) del objeto de juego 
    donde se aplica el cambio.
    */
    uint32_t getId() const;

    /*
    Devuelve la nueva coordenada (float) X,
    del objeto de juego referido.
    */
    float getX() const;

    /*
    Devuelve la nueva coordenada (float) Y,
    del objeto de juego referido.
    */
    float getY() const;
};

#endif // OBJECT_MOVE_CHANGE_H
