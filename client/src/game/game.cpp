#include "../../includes/game/game.h"

#include <connector/connector.h>
#include <blocking_queue.h>
#include <thread_safe_queue.h>

#include "../../includes/threads/event_game_receiver_thread.h"
#include "../../includes/threads/key_sender_thread.h"
#include "../../includes/threads/playing_loop_thread.h"
#include "../../includes/threads/play_result.h"

#include "../../includes/sdl_system.h"
#include "../../includes/window/window.h"
#include "../../includes/mixer/mixer.h"
#include "../../includes/mixer/portal_mixer.h"

#include <configs_yaml/config_paths.h>
#include <yaml-cpp/yaml.h>

#include <mutex>
#include <condition_variable>
#include <portal_exception.h>

#include <iostream>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define VOLUME_MUSIC 10


Game::Game(Connector &connector, uint8_t game_id, 
            uint32_t player_id, uint8_t mapId)
:   isDead(true),
    connector(std::move(connector)), 
    gameId(game_id), 
    playerId(player_id), 
    mapId(mapId),
    threads(),
    changesMade(),
    changesAsk(),
    mutex()
    {}

void Game::operator()() {
    this->run();
}

/*
PRE: Recibe un doble referencia a otra juego (Game &&).
POST: Inicializa un nuevo juego por movimiento semantico.
*/
Game::Game(Game && other)
:   isDead(true), 
    connector(std::move(other.connector)),
    gameId(other.gameId),
    playerId(other.playerId),
    mapId(other.mapId),
    threads(std::move(other.threads)),
    changesMade(std::move(other.changesMade)),
    changesAsk(std::move(other.changesAsk)),
    stopQueue(std::move(stopQueue)),
    videoFramesQueue(std::move(videoFramesQueue)),
    mutex() {}

/*Ejecuta el juego.*/
void Game::run(){
    {
        std::unique_lock<std::mutex> l(this->mutex);
        this->isDead = false;    
    }
    //Cargo YAML
    std::string mapFile;
    connector >> mapFile;
    YAML::Node baseNode = YAML::Load(mapFile);

    uint8_t start;
    std::cout << "Waiting for other players ... \n";
    connector >> start;
    if ((EventType) start != game_starts ) {
        this->stop();
        throw PortalException("Game could not start");
    }
    std::cout << "Game is about to start.\n";

    //ThreadSafeQueue<ThreadStatus> stopQueue;
    //BlockingQueue<std::vector<char>> videoFramesQueue;

    //Inicializo SDL
    SdlSystem sdlSystem;
    sdlSystem.init_video();
    sdlSystem.init_audio();

    
    //Inicializo resultado del juego
    PlayResult playResult(baseNode);

    //Inicializo Window
    int windowWidthPixels = WINDOW_WIDTH;
    int windowHeightPixels = WINDOW_HEIGHT;
    Window window(windowWidthPixels, windowHeightPixels, this->playerId, baseNode);
    
    //Inicializo Mixer
    PortalMixer portalMixer;
    Mixer mixer = std::move(portalMixer.create_mixer());
    mixer.volume_music(VOLUME_MUSIC);
    mixer.play_music();

    this->threads.push_back(std::move(std::unique_ptr<Thread>(
        new EventGameReceiverThread(this->connector, this->changesMade, this->stopQueue)
    )));
    this->threads.push_back(std::move(std::unique_ptr<Thread>(
        new KeySenderThread(this->connector, this->changesAsk, this->stopQueue)
    )));
    PlayingLoopThread playingLoop(this->changesMade, 
                                  this->changesAsk, 
                                  window, 
                                  mixer, 
                                  playResult, 
                                  this->stopQueue,
                                  videoFramesQueue
                                  );

    for (auto & thread : this->threads){
        (*thread).start();
    }
    playingLoop.run();
    this->stop();
    playResult.print();
}

/*Detiene la ejecucion del juego.*/
void Game::stop(){
    std::unique_lock<std::mutex> l(this->mutex);
    this->changesAsk.close();
    this->videoFramesQueue.close();
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
