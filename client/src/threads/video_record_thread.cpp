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
    videoFileName(videoFileName),
    videoWidth(videoWidth),
    videoHeight(videoHeight),
    videoFramesQueue(videoFramesQueue),
    mutex() {}
// outputFormat(videoFileName, videoWidth, videoHeight),
VideoRecordThread::~VideoRecordThread() = default;

/*Graba frames de video recibido en disco.*/
void VideoRecordThread::run(){
    {
        std::unique_lock<std::mutex> l(this->mutex);
        this->isDead = false;
    }
    OutputFormat outputFormat(this->videoFileName,this->videoWidth,this->videoHeight);
    std::vector<char> videoFrameBuffer;
    while ((! this->is_dead()) && this->videoFramesQueue.pop(videoFrameBuffer)){
        outputFormat.write_frame(videoFrameBuffer.data()); //this->
    }
    this->stop();
}

/*Detiene la ejecucion del hilo.*/
void VideoRecordThread::stop(){
    //std::unique_lock<std::mutex> l(this->mutex);
    //this->isDead = true;
}

/*
Devuelve true si el hilo esta muerto; 
false en caso contrario.
*/
bool VideoRecordThread::is_dead(){
    std::unique_lock<std::mutex> l(this->mutex);
    return this->isDead;
}
