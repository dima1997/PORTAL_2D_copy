#include "../../includes/game/game.h"

#include <connector/connector.h>
#include <blocking_queue.h>
#include <thread_safe_queue.h>

#include "../../includes/threads/animation_loop_thread.h"
#include "../../includes/threads/event_game_receiver_thread.h"
#include "../../includes/threads/key_sender_thread.h"
#include "../../includes/threads/key_reader_thread.h"
#include "../../includes/window/window.h"

#include <mutex>
#include <condition_variable>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480


Game::Game(Connector &connector, uint8_t game_id, uint8_t player_id)
:   connector(std::move(connector)), gameId(game_id), playerId(player_id), 
    isDead(true) {}

void Game::operator()() {
    uint8_t finished;
    connector >> finished;
}

/*
PRE: Recibe un doble referencia a otra juego (Game &&).
POST: Inicializa un nuevo juego por movimiento semantico.
*/
Game::Game(Game && other)
:   connector(std::move(other.connector)),
    gameId(other.gameId),
    playerId(other.playerId),
    threads(std::move(other.threads)),
    isDead(true) {}
/*
    mutex(std::move(other.mutex)),
    cv(std::move(other.cv)),
*/

/*Ejecuta el juego.*/
void Game::run(){
    ThreadSafeQueue<std::unique_ptr<ObjectMovesEvent>> changesMade;
    BlockingQueue<std::unique_ptr<GameAction>> changesAsk;
    int windowWidthPixels = WINDOW_WIDTH;
    int windowHeightPixels = WINDOW_HEIGHT;
    Window window(windowWidthPixels, windowHeightPixels, this->playerId);
    const Area & areaChell = window.getMainTextureArea(); 
    this->threads.push_back(std::move(std::unique_ptr<Thread>(new KeyReaderThread(areaChell, changesAsk, *this))));
    this->threads.push_back(std::move(std::unique_ptr<Thread>(new AnimationLoopThread(window, changesMade))));
    this->threads.push_back(std::move(std::unique_ptr<Thread>(new EventGameReceiverThread(this->connector, changesMade, *this))));
    this->threads.push_back(std::move(std::unique_ptr<Thread>(new KeySenderThread(this->connector, changesAsk))));
    for (int i = 0; i < this->threads.size(); ++i){
        (*(this->threads[i])).start();
    }
    std::unique_lock<std::mutex> l(this->mutex);
    this->cv.wait(l, [this]{ return this->is_dead();});
}

/*Detiene la ejecucion del juego.*/
void Game::stop(){
    std::unique_lock<std::mutex> l(this->mutex);
    for (int i = 0; i < this->threads.size(); ++i){
        (*(this->threads[i])).stop();
        (*(this->threads[i])).join();
    }
    this->isDead = true; 
    this->cv.notify_one();
}

/*Devuelve true si el hilo esta muerto.*/
bool Game::is_dead(){
    std::unique_lock<std::mutex> l(this->mutex);
    return this->isDead;
}
