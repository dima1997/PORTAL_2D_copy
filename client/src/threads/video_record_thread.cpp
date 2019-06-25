#include "../../includes/threads/video_record_thread.h"

#include "../../includes/window/record/output_format.h"

#include <thread.h>
#include <blocking_queue.h>
#include <thread_safe_queue.h>
#include <protocol/protocol_code.h>

#include <vector>
#include <mutex>
#include <ctime>
#include <iostream>

#define TIME_MAX_LEN 30
#define VIDEO_FILE_BEGIN "video_portal_"
#define VIDEO_FILE_END ".mp4"

/*
PRE: Recibe: 
    las dimensiones del video : ancho y alto (int);
    una cola bloqueante por donde recibir los frames de 
    video a escribir en disco.
    una cola segura por donde indicarle al hilo principal 
    que termino de ejecutar por cierta razon.
POST: 
*/
VideoRecordThread::VideoRecordThread(
    int videoWidth,
    int videoHeight,
    BlockingQueue<std::vector<char>> & videoFramesQueue,
    ThreadSafeQueue<ThreadStatus> & stopQueue
)
:   isDead(true),
    width(videoWidth),
    height(videoHeight),
    videoFramesQueue(videoFramesQueue),
    stopQueue(stopQueue),
    mutex() {}

/*Destruye el hilo grabador de video.*/
VideoRecordThread::~VideoRecordThread() = default;

/*Graba frames de video recibido en disco.*/
void VideoRecordThread::run(){
    {
        std::unique_lock<std::mutex> l(this->mutex);
        this->isDead = false;
    }
    try {
        std::vector<char> videoFrameBuffer;
        if (! this->videoFramesQueue.pop(videoFrameBuffer)){
            this->_stop();
            return;
        }
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[TIME_MAX_LEN];
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer,sizeof(buffer),"%d_%m_%Y_%H_%M_%S",timeinfo);
        std::string actualTimeStr(buffer);
        std::string videoFileName = VIDEO_FILE_BEGIN + actualTimeStr + VIDEO_FILE_END;
        OutputFormat outputFormat(videoFileName, this->width, this->height);

        while ((! this->is_dead()) && this->videoFramesQueue.pop(videoFrameBuffer)){
            outputFormat.write_frame(videoFrameBuffer.data());
        }
        this->_stop();
    } catch (std::exception & error) {
        std::cerr << error.what();
    }
    if (! this->is_dead()){
        ThreadStatus statusStop = THREAD_STOP;
        this->stopQueue.push(statusStop);
    }
    
}

/*
Cerrar cola bloqueante desde afuera, 
para terminar la ejecucion del hilo.
*/
void VideoRecordThread::stop(){
    //No hace nada
}

/*Detiene la ejecucion del hilo*/
void VideoRecordThread::_stop(){
    std::unique_lock<std::mutex> l(this->mutex);
    this->isDead = true;
}

/*
Devuelve true si el hilo esta muerto; 
false en caso contrario.
*/
bool VideoRecordThread::is_dead(){
    std::unique_lock<std::mutex> l(this->mutex);
    return this->isDead;
}
