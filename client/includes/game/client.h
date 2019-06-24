#ifndef PORTAL_CLIENT_H
#define PORTAL_CLIENT_H

#include <string>

class Client {
public:
    Client();
    /*
    PRE: Recibe:
        el host (string) y el port (string) a donde conectarse;
        el comando de linea a utilizar ("new" o  "join")
        y un id correspondiente en el primer caso al mapa de juego,
        y en el segundo al id de juego;
    POST: Ejecuta el juego en modo rapido, sin ningun tipo de interfaz 
    de log-in.
    */
    void operator()(std::string &host, std::string &port, std::string &command, uint8_t id);
    
    /*
    Ejecuta el cliente en modo por 
    linea de comando.
    */
    void run_line();

    /*
    PRE: Recibe los argumentso del main.
    POST: Ejecuta el cliente en modo ventanas 
    graficas de qt.
    */
    void run_qt(int argc, char **argv);
};

#endif //PORTAL_CLIENT_H
