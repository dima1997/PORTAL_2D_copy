#ifndef VIDEO_RECORD_THREAD_H
#define VIDEO_RECORD_THREAD_H

#include "../window/record/output_format.h"

#include <thread.h>
#include <blocking_queue.h>

#include <vector>
#include <mutex>

class VideoRecordThread : public Thread {
private:
    bool isDead;
    OutputFormat outputFormat;
    BlockingQueue<std::vector<char>> & videoFramesQueue;
    std::mutex mutex;

public:
    /*
    PRE: Recibe: 
        el nombre con el que se guardara el video grabado;
        las dimensiones del video : ancho y alto (int);
        una cola bloqueante por donde recibir los frames de 
        video a escribir en disco.
    POST: 
    */
    VideoRecordThread(
        const std::string & videoFileName,
        int videoWidht,
        int videoheight,
        BlockingQueue<std::vector<char>> & videoFramesQueue
    );

    ~VideoRecordThread();

    /*Graba frames de video recibido en disco.*/
    void run();

    /*Detiene la ejecucion del hilo.*/
    void stop();

    /*
    Devuelve true si el hilo esta muerto; 
    false en caso contrario.
    */
    bool is_dead();
};

#endif // VIDEO_RECORDER_THREAD_H
