#include "../../includes/user_interface/line_interface.h"

#include "../../includes/user_interface/message_exception.h"
#include "../../includes/game/game.h"
#include <portal_exception.h>
#include <protocol/protocol_code.h>
#include <connector/connector.h>
#include <connector/socket_exception.h>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <sstream>

#define COMMAND_NEW "new"
#define COMMAND_JOIN "join"
#define COMANDO_QUIT "q"

LineInterface::LineInterface(bool & keepInput)
:   keepInput(keepInput) {}

LineInterface::~LineInterface() = default;

void LineInterface::keep_input(std::string & wantToQuit){
    if (wantToQuit == "q"){
        this->keepInput = false;
        throw MessageException("Quiting game.");
    }
}

Connector LineInterface::log_to_server(){
    try {
        std::cout << "Put ip local (example : localhost) or ";
        std::cout << "'" << COMANDO_QUIT << "' to quit: \n";
        std::string host;
        std::getline(std::cin, host);
        this->keep_input(host);
        std::cout << "Put server port (example : 8082) to connect ";
        std::cout << "'" << COMANDO_QUIT << "' to quit: \n";
        std::string port;
        std::getline(std::cin, port);
        this->keep_input(port);
        return std::move(Connector(host, port));
    } catch (SocketException &error){
        std::stringstream msg;
        msg << "Could no make connection:\n";
        msg << "Check ip and/or port.\n";
        msg << "Maybe server is not working." << std::endl;
        throw MessageException(msg.str());        
    }
}

std::string LineInterface::choose_game_mode(){
    std::cout << "Put '"<< COMMAND_NEW <<"' to start new game, ";
    std::cout << "'" << COMMAND_JOIN <<"' to join game in stock";
    std::cout << " or '" << COMANDO_QUIT << "' to quit :\n";
    std::string command;
    std::getline(std::cin, command);
    this->keep_input(command);
    return std::move(command);
} 

uint8_t LineInterface::choose_map_id(std::vector<uint8_t> & mapIds){
    std::cout << "Choose one of the next map ids or ";
    std::cout << "'" << COMANDO_QUIT "' to quit :\n";
    std::cout << "Map ids : \n";
    for (int i = 0; i < (int)mapIds.size(); ++i){
        std::cout << (unsigned) mapIds[i] << "\n";
    }
    std::string mapIdStr;
    std::getline(std::cin, mapIdStr);
    this->keep_input(mapIdStr);
    std::string::const_iterator it = mapIdStr.begin();
    while (it != mapIdStr.end() && std::isdigit(*it)) ++it;
    if (!(!mapIdStr.empty() && it == mapIdStr.end())){
        throw MessageException("Wrong map id.");
    }
    uint8_t mapId = (uint8_t) std::stoi(mapIdStr); 
    if (std::find(mapIds.begin(),mapIds.end(),mapId) == mapIds.end()){
        throw MessageException("Wrong map id.");
    }
    return  mapId;
}

std::string LineInterface::choose_game_name(){
    std::cout << "Put name of this game ";
    std::cout << " or '" << COMANDO_QUIT << "' to quit :\n";
    std::string gameName;
    std::getline(std::cin, gameName);
    this->keep_input(gameName);
    return std::move(gameName);
} 

Game LineInterface::_get_new_game(Connector & connector, 
                                  uint8_t mapId, 
                                  std::string & gameName){
    connector << mapId;
    connector << gameName;
    uint8_t status;
    connector >> status;
    if (status != command_ok){
        throw MessageException("Server rejected game creation.");
    }
    uint8_t gameId;
    connector >> gameId;
    uint32_t playerId;
    connector >> playerId;
    std::cout << "Starting game :\n";
    std::cout << "Game name : " << gameName << "\n";
    std::cout << "Game id : " << (unsigned) gameId << "\n";
    std::cout << "Player id : " << playerId << "\n";
    std::cout << "Map id : " << (unsigned) mapId << "\n";
    return std::move(Game(connector, gameId, playerId, mapId));
} 

Game LineInterface::get_new_game(Connector & connector){
    connector << (uint8_t) new_game;
    // TODO : Pedir mapas al servidor
    // Ids de mapa hard-codeados
    std::vector<uint8_t> mapIds;
    for (uint8_t i = 0; i < 3; ++i){
        mapIds.push_back(i);
    }
    uint8_t mapId = this->choose_map_id(mapIds);
    std::string gameName = this->choose_game_name();
    return std::move(this->_get_new_game(connector, mapId, gameName));
}

uint8_t LineInterface::choose_game_id
(std::map<uint8_t,std::string> & stockGames){
    std::cout << "Put one of the next game ids in stock,";
    std::cout << "or '"<< COMANDO_QUIT << "' to quit :\n";
    std::cout << "Game stock :\n";
    for (std::map<uint8_t,std::string>::iterator it=stockGames.begin(); 
         it!=stockGames.end(); ++it){
        std::cout << "Game id : " << (unsigned) it->first;
        std::cout << " - Game name : " << it->second << "\n";
    }

    std::string gameIdStr;
    std::getline(std::cin, gameIdStr);
    this->keep_input(gameIdStr);
    std::string::const_iterator it = gameIdStr.begin();
    while (it != gameIdStr.end() && std::isdigit(*it)) ++it;
    if (!(!gameIdStr.empty() && it == gameIdStr.end())){
        throw MessageException("Wrong game id.");
    }
    uint8_t gameId = (uint8_t) std::stoi(gameIdStr);
    if (stockGames.count(gameId) == 0){
        throw MessageException("Wrong game id.");
    }
    return gameId; 
}

Game LineInterface::_get_join_game(Connector & connector, uint8_t gameId){
    uint8_t status;
    connector >> status;
    if (status == command_ok) {
        uint32_t playerId;
        connector >> playerId;
        // TODO : Pedir mapa
        uint8_t mapId = 0;
        std::cout << "Joining game.\n";
        std::cout << "Game id :" << (unsigned) gameId << "\n";
        std::cout << "Player id : " << playerId << "\n";
        std::cout << "Map id : " << (unsigned) mapId << "\n";
        return std::move(Game(connector, gameId, playerId, mapId));
    } 
    if (status == game_is_full) {
        std::stringstream msg;
        msg << "Game " << (unsigned) gameId << " is full." << std::endl;
        throw MessageException(msg.str());
    } 
    if (status == non_existent_game) {
        std::stringstream msg;
        msg << "Game " << (unsigned) gameId << " does not exist." << std::endl;
        throw MessageException(msg.str());
    }
    throw MessageException("Unexpected error...");

}

Game LineInterface::get_join_game(Connector & connector){
        connector << (uint8_t) join_game;
        uint8_t gameCount;
        connector >> gameCount;
        if (gameCount == 0){
            throw MessageException("No games in stock.");
        }
        std::map<uint8_t,std::string> stockGames;
        for (uint8_t i = 0; i < gameCount; ++i) {
            uint8_t gameId;
            connector >> gameId;
            std::string gameName;
            connector >> gameName;
            std::pair<uint8_t,std::string> oneGame(gameId, gameName);
            stockGames.insert(oneGame);
        }
        uint8_t gameId = this->choose_game_id(stockGames);
        connector << (uint8_t) gameId;
        return std::move(this->_get_join_game(connector, gameId));
}

Game LineInterface::create_game(){
    Connector connector = this->log_to_server();
    std::string command = this->choose_game_mode();
    if (command == COMMAND_NEW){
        return std::move(this->get_new_game(connector));
    } else if (command == COMMAND_JOIN){
        return std::move(this->get_join_game(connector));
    } else {
        throw MessageException("Wrong game mode.");
    }
}