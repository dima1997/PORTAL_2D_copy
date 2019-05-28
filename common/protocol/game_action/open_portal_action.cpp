    /*
    PRE: Recibe el nombre de una accion del juego (GameActionName); 
    y unas coordenadas x,y (float).
    POST: Inicializa un accion del juego con coordenadas.
    */
    explicit CoordsAction(GameActionName gameActionName, float x, float y);

    CoordsAction();

    /*Destruye una accion del juego con coordenadas.*/
    virtual ~CoordsAction();

    /*
    PRE: Recibe un conector (Connector &).
    POST: La accion se envia a traves del conector.
    */
    virtual void sendThrough(Connector &out) const;
    
    /*
    PRE: Recibe un conector (Connector &).
    POST: La accion se recibe desde el conector.
    */
    virtual void receiveFrom(Connector &out);

    /*Devuelve la coordenada x de la accion con coordenadas.*/
    float getX();

    /*Devuelve la coordenada y de la accion con coordenadas.*/
    float getY();