#include "../../includes/game/game.h"

#include <connector/connector.h>
#include <blocking_queue.h>
#include <thread_safe_queue.h>

#include "../../includes/threads/event_game_receiver_thread.h"
#include "../../includes/threads/key_sender_thread.h"

#include "../../includes/threads/playing_loop_thread.h"

#include "../../includes/window/window.h"

#include "../../includes/textures/common_texture/texture_change.h"

#include <mutex>
#include <condition_variable>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480


Game::Game(Connector &connector, uint8_t game_id, 
            uint32_t player_id, uint8_t mapId)
:   connector(std::move(connector)), gameId(game_id), 
    playerId(player_id), mapId(mapId), isDead(true) {}

void Game::operator()() {
    this->run();
}

/*
PRE: Recibe un doble referencia a otra juego (Game &&).
POST: Inicializa un nuevo juego por movimiento semantico.
*/
Game::Game(Game && other)
:   connector(std::move(other.connector)),
    gameId(other.gameId),
    playerId(other.playerId),
    mapId(other.mapId),
    isDead(true), 
    threads(std::move(other.threads)),
    changesMade(std::move(other.changesMade)),
    changesAsk(std::move(other.changesAsk)) {}

/*Ejecuta el juego.*/
void Game::run(){
    {
        std::unique_lock<std::mutex> l(this->mutex);
        this->isDead = false;    
    }
    BlockingQueue<GameActionName> endQueue;
    int windowWidthPixels = WINDOW_WIDTH;
    int windowHeightPixels = WINDOW_HEIGHT;
    Window window(windowWidthPixels, windowHeightPixels, this->playerId, this->mapId + 1);
    this->threads.push_back(std::move(std::unique_ptr<Thread>(new EventGameReceiverThread(this->connector, this->changesMade, endQueue, playerId))));
    this->threads.push_back(std::move(std::unique_ptr<Thread>(new KeySenderThread(this->connector, this->changesAsk))));
    this->threads.push_back(std::move(std::unique_ptr<Thread>(new PlayingLoopThread(window, this->changesMade, this->changesAsk, endQueue))));

    for (auto & thread : this->threads){
        (*thread).start();
    }
    GameActionName actionName;
    endQueue.pop(actionName);
    this->stop();
    // Mostrar pantalla de Perder/Ganar
}

/*Detiene la ejecucion del juego.*/
void Game::stop(){
    std::unique_lock<std::mutex> l(this->mutex);
    this->changesAsk.close();
    for (int i = 0; i < (int)this->threads.size(); ++i){
        (*(this->threads[i])).stop();
        (*(this->threads[i])).join();
    }
    this->isDead = true; 
}

/*Devuelve true si el hilo esta muerto.*/
bool Game::is_dead(){
    std::unique_lock<std::mutex> l(this->mutex);
    return this->isDead;
}
