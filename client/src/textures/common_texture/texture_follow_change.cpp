    /*
    PRE: Recibe:
        el id de una textura seguidora;
        el id de una textura a seguir;
    POST: Inicializa un cambio de empezar a seguir
    una textura.
    */
    StartFollowChange::StartFollowChange(
        uint32_t idFollowing, 
        uint32_t idFollwed
    );

    /*
    Destruye el cambio de seguimiento de la textura.
    */
    StartFollowChange::~StartFollowChange();

    /*
    PRE: Recibe un ventana (Window &) donde 
    realizar el cambio.
    POST: Realiza el cambio que representa 
    en la ventana recibida.
    */
    void StartFollowChange::change(Window &window);   