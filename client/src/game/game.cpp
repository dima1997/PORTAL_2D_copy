#include "../../includes/game/game.h"

#include <connector/connector.h>
#include <blocking_queue.h>
#include <thread_safe_queue.h>

#include "../../includes/threads/event_game_receiver_thread.h"
#include "../../includes/threads/key_sender_thread.h"
#include "../../includes/threads/playing_loop_thread.h"
#include "../../includes/threads/play_result.h"
#include "../../includes/threads/video_record_thread.h"

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

#define VIDEO_FILE_NAME "portal_video_"
#define VIDEO_FILE_END ".mp4"
#define VIDEO_WIDTH 640
#define VIDEO_HEIGHT 480
#define VOLUME_MUSIC 10


Game::Game(Connector &connector, uint8_t game_id, 
            uint32_t player_id, std::string & mapYaml)
:   connector(std::move(connector)), 
    gameId(game_id), 
    playerId(player_id), 
    mapYaml(mapYaml),
    threads(),
    changesMade(),
    changesAsk(),
    stopQueue(),
    videoFramesQueue(),
    mutex()
    {}

/*
PRE: Recibe un doble referencia a otra juego (Game &&).
POST: Inicializa un nuevo juego por movimiento semantico.
*/
Game::Game(Game && other)
:   connector(std::move(other.connector)),
    gameId(other.gameId),
    playerId(other.playerId),
    mapYaml(other.mapYaml),
    threads(std::move(other.threads)),
    changesMade(std::move(other.changesMade)),
    changesAsk(std::move(other.changesAsk)),
    stopQueue(std::move(other.stopQueue)),
    videoFramesQueue(std::move(other.videoFramesQueue)),
    mutex() {}

/*Ejecuta el juego.*/
PlayResult Game::operator()(){
    std::cout << "Waiting for other players ... \n";
    YAML::Node mapNode = YAML::Load(this->mapYaml);

    //Inicializo SDL
    SdlSystem sdlSystem;
    sdlSystem.init_video();
    sdlSystem.init_audio();

    //Inicializo resultado del juego
    PlayResult playResult(mapNode);

    //Inicializo Window
    int windowWidthPixels = VIDEO_WIDTH;
    int windowHeightPixels = VIDEO_HEIGHT;
    Window window(windowWidthPixels, windowHeightPixels, this->playerId, mapNode);
    
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

    BlockingQueue<std::vector<char>> videoFramesQueue;
    
    std::stringstream videoFileName;
    videoFileName << VIDEO_FILE_NAME << this->playerId << VIDEO_FILE_END;
    this->threads.push_back(std::move(std::unique_ptr<Thread>(
        new VideoRecordThread(
            videoFileName.str(),
            VIDEO_WIDTH,
            VIDEO_HEIGHT,
            this->videoFramesQueue
        )
    )));
    PlayingLoopThread playingLoop(this->changesMade, 
                                  this->changesAsk, 
                                  window, 
                                  mixer, 
                                  playResult, 
                                  this->stopQueue,
                                  this->videoFramesQueue
                                  );
    for (auto & thread : this->threads){
        (*thread).start();
    }
    playingLoop.run();
    this->stop();
    return playResult;
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
}