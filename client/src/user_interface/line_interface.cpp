#include <portal_exception.h>

#define COMMAND_NEW "new"
#define COMMAND_JOIN "join"
#define COMANDO_QUIT "q"

LineInterface::LineInterface()
:   keepInput(true) {}

LineInterface::~LineInterface() = default;

bool LineInterface::keep_input(std::string & wantToQuit){
    if (wantToQuit == "q"){
        this->keepInput = false;
    }
    return this->keepInput;
}

bool LineInterface::log_to_server(Connector & connector){
    try {
        std::cout << "Ingrese su ip local (ejemplo: localhost) o 'q' para salir: \n";
        std::string host;
        std::getline(std::cin, host);
        if (! this->keep_input(host)){
            return false;
        }
        std::cout << "Ingrese el puerto del servidor al cual conectarse o 'q' para salir : \n";
        std::string port;
        std::geline(std::cint, port);
        if (! this->keep_input(host)){
            return false;
        }
        connector = std::move(Connector(host, port));
        return true;
    } catch (SocketException &error){
        std::cout << "Ip y/o puerto elegido/s invalido/s.\n";
        return false;
    }
}

 LineInterface::choose_game_mode(std::string & command){
    std::cout << "Ingrese '"<< COMMAND_NEW <<"' para iniciar una nueva parida,";
    std::cout << "'" << COMMAND_JOIN <<"' para unirse a una existente";
    std::cout << "o '" << COMANDO_QUIT << "' para salir :\n";
    std::getline(std::cint, command);
    this->keep_input(command);
    return std::move(command);
} 

bool LineInterface::choose_map_id(uint8_t & mapId, std::vector<uint8_t> & mapIds){
    std::cout << "Elija uno de los siguientes ids de mapa o ";
    std::cout << "'" << COMANDO_QUIT "' para salir :\n"
    std::cout << "Ids de Mapa : \n";
    for (int i = 0; i < mapIds.size(); ++i){
        std::cout << (unsigned) mapIds[i] << "\n";
    }
    std::string mapIdStr;
    std::getline(std::cin, mapIdStr);
    if (! this->keep_input(mapIdStr)){
        return false;
    }
    std::string::const_iterator it = mapIdStr.begin();
    while (it != mapIdStr.end() && std::isdigit(*it)) ++it;
    if (!(!mapIdStr.empty() && it == mapIdStr.end())){
        std::cout << "Id de mapa invalido.\n" << "\n";
        return false;
    }
    if (std::find(mapIds.begin(),mapIds.end(),mapId) != mapIds.end()){
        std::cout << "Id de mapa invalido.\n" << "\n";
        return false;
    }
    mapId = (uint8_t) std::stoi(mapIdStr); 
    return true;
}

bool LineInterface::choose_game_name(std::string & gameName){
    std::cout << "Ingrese que nombre desea asignarle a este juego";
    std::cout << " o '" << COMANDO_QUIT << "' para salir :\n";
    std::geline(std::cin, gameName);
    return this->keep_input(gameName);
} 

bool LineInterface::_config_new_game(Connector & connector, Game & game, 
                                    uint8_t mapId, std::string & gameName){
    connector << (uint8_t) new_game;
    connector << mapId;
    connector << gameName;

    uint8_t status;
    connector >> status;
    if (status != command_ok){
        std::cout << "Creacion de partida rechazada por servidor.\n";
        return false;
    }

    uint8_t gameId;
    connector >> gameId;
    uint32_t playerId;
    connector >> playerId;

    std::cout << "Iniciando partida :\n";
    std::cout << "Nombre de partida : " << gameName << "\n";
    std::cout << "Id de partida : " << (unsigned) gameId << "\n";
    std::cout << "Id de jugador : " << playerId << "\n";
    std::cout << "Id de mapa : " << mapId << "\n";

    game = std::move(Game(connector, gameId, playerId, mapId));
    return true;
} 

bool LineInterface::config_new_game(Connector & connector, Game & game){
    // TODO : Pedir mapas al servidor
    // Ids de mapa hard-codeados
    std::vector<uint8_t> mapIds;
    for (uint8_t i = 0; i < 1; ++i){
        mapIds.push_back(i);
    }
    uint8_t mapId;
    if (! this->choose_map_id(mapId, mapIds)){
        return false;
    }
    std::string gameName;
    if (! this->choose_game_name(gameName)){
        return false;
    }
    if (! this->keep_input(gameName)){
        return false;
    }
    return this->_config_new_game(connector, game, mapId, gameName);
}

LineInterface::config_join_game(Connector & connector, Game & game){
        connector << (uint8_t) join_game;
        // TODO: show user all options and choose one
        uint8_t gameCount;
        connector >> gameCount;
        if (gameCount == 0){
            std::cout << "No hay partidas disponibles.\n";
        }
        for (uint8_t i = 0; i < gameCount; ++i) {
            uint8_t gameId;
            connector >> gameId;
            std::string gameName;
            connector >> gameName;
            std::cout << "Id partida : " << (unsigned) gameId;
            std::cout << " - Nombre partida : " << gameName << "\n";
        }
        // ---
        connector << (uint8_t) id;
        uint8_t status;
        connector >> status;
        std::cout << (unsigned) status << std::endl;
        if (status == command_ok) {
            uint8_t player_id;
            connector >> player_id;
            std::cout << (unsigned) player_id << std::endl;
            return std::move(Game(connector, id, player_id));
        } else if (status == game_is_full) {
            std::stringstream msg;
            msg << "Game " << (unsigned) id << " is full." << std::endl;
            throw PortalException(msg.str());
        } else if (status == non_existent_game) {
            std::stringstream msg;
            msg << "Game " << (unsigned) id << " does not exist." << std::endl;
            throw PortalException(msg.str());
        } else {
            throw PortalException("Unexpected error...\n");
        }
}

/*
Pre: Recibe una referencia a un juego no configurado (Game &);
POST: Devuelve true si se configuro el juego, false en caso contrario 
dado datos mal ingresados por el usuario u otro error proveniente del 
servidor.
*/
bool LineInterface::config_game(Game & game){
    Connector connector;
    if (! this->log_to_server(connector)){
        return false;
    }
    std::string command; 
    if (! this->choose_game_mode(command)){
        return false;
    }
    if (command == COMMAND_NEW){
        return this->config_new_game(connector,game);
    } else if (command == COMMAND_JOIN){

    } else {
        std::cout << "Opcion de juego invalida.\n";
        return false;
    }


    
}