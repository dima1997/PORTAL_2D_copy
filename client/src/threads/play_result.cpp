#include "../../includes/threads/play_result.h"

#include <portal_exception.h>
#include <yaml-cpp/yaml.h>
#include <cstdint>
#include <string>
#include <map>
#include <iostream>
#include <sstream>

const std::map<GameStatus,std::string> GAME_STATUS_STR(
    {
        std::make_pair(WON, "Won"),
        std::make_pair(LOST, "Lost"),
        std::make_pair(NOT_FINISHED, "Not finished")
    }
);

const std::map<PlayerStatus,std::string> PLAYER_STATUS_STR(
    {
        std::make_pair(ALIVE, "Alive"),
        std::make_pair(DEAD, "Dead"),
    }
);

/*
PRE: Recibe el nodo base de YAML (YAML::Node) de
la configutacion de juego actual.
POST: Inicializa un resultado de juego.
*/
PlayResult::PlayResult(YAML::Node & gameConfig){
    YAML::Node playerIdsNode = gameConfig["chells"]["id_coordinates"];
    for (int i = 0; i < (int)playerIdsNode.size(); ++i){
        uint32_t id = playerIdsNode[i]["id"].as<uint32_t>();
        this->playersStatus.insert(std::make_pair(id, ALIVE));
    }
    this->gameStatus = NOT_FINISHED;
}

/*Destruye el estado del juego.*/
PlayResult::~PlayResult() = default;

/*
Setea el status (PlayerStatus) del jugador 
de id (uint32_t) recibido.
Levanta PortalException si no existe jugador 
con dicho id.  
*/
void PlayResult::setPlayerStatus(uint32_t id, PlayerStatus status){
    if (this->playersStatus.count(id) == 0){
        std::stringstream err;
        err << "Not player with id: " << id << "\n";
        throw PortalException(err.str().c_str());
    }
    this->playersStatus[id] = status;
}

/*Setea el estado (GameStatus) del juego.*/
void PlayResult::setGameStatus(GameStatus status){
    this->gameStatus = status;
}

/*Imprime el resultado del juego por salida estandar.*/
void PlayResult::print(){
    std::cout << "!!! Game Over !!! \n";
    std::cout << "Game status : " << GAME_STATUS_STR.at(this->gameStatus);
    std::cout << "\n";
    for (std::map<uint32_t,PlayerStatus>::iterator 
         it=this->playersStatus.begin(); 
         it!=this->playersStatus.end(); 
         ++it){
        uint32_t id = it->first;
        PlayerStatus status = it->second;
        std::cout << "Player id : " << id << "\n";
        std::cout << "\t- Status : " << PLAYER_STATUS_STR.at(status);
        std::cout << "\n"; 
    }
}

/*
PRE: Recibe el id (uint32_t) de un jugador.
POST: Devuelve true si el jugador esta vivo; 
false en caso contrario.
Levanta PortalException si no existe jugador 
con dicho id.  
*/
bool PlayResult::is_player_alive(uint32_t id){
    if (this->playersStatus.count(id) == 0){
        std::stringstream err;
        err << "Not player with id: " << id << "\n";
        throw PortalException(err.str().c_str());
    }
    return (this->playersStatus.at(id) == ALIVE);
}

/*
Devuelve el id (uint32_t) de un jugador vivo.
Si no hay jugadores vivos devuelve (uint32_t)(-1)
*/
uint32_t PlayResult::get_player_alive(){ 
    for (std::map<uint32_t,PlayerStatus>::iterator 
         it=this->playersStatus.begin(); 
         it!=this->playersStatus.end(); 
         ++it){
        uint32_t id = it->first;
        PlayerStatus status = it->second;
        if (status == ALIVE){
            return id;
        }
    }
    return (uint32_t)(-1);
}