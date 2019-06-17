#include "../../includes/threads/video_record_thread.h"

#include "../../includes/window/record/output_format.h"

#include <thread.h>
#include <blocking_queue.h>

#include <vector>
#include <mutex>

/*
PRE: Recibe: 
    el nombre con el que se guardara el video grabado;
    las dimensiones del video : ancho y alto (int);
    una cola bloqueante por donde recibir los frames de 
    video a escribir en disco.
POST: 
*/
VideoRecordThread::VideoRecordThread(
    const std::string & videoFileName,
    int videoWidth,
    int videoHeight,
    BlockingQueue<std::vector<char>> & videoFramesQueue
)
:   isDead(true),
    outputFormat(videoFileName,videoWidth,videoHeight),
    videoFramesQueue(videoFramesQueue),
    mutex() {}

/*Destruye el hilo grabador de video.*/
VideoRecordThread::~VideoRecordThread() = default;

/*Graba frames de video recibido en disco.*/
void VideoRecordThread::run(){
    {
        std::unique_lock<std::mutex> l(this->mutex);
        this->isDead = false;
    }
    std::vector<char> videoFrameBuffer;
    while ((! this->is_dead()) && this->videoFramesQueue.pop(videoFrameBuffer)){
        this->outputFormat.write_frame(videoFrameBuffer.data());
    }
    this->stop();
}

/*Detiene la ejecucion del hilo.*/
void VideoRecordThread::stop(){
    // Con cerrar la cola bloqueante 
    // desde afuera es suficiente
}

/*
Devuelve true si el hilo esta muerto; 
false en caso contrario.
*/
bool VideoRecordThread::is_dead(){
    std::unique_lock<std::mutex> l(this->mutex);
    return this->isDead;
}
