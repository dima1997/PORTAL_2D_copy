#ifndef VIDEO_RECORD_THREAD_H
#define VIDEO_RECORD_THREAD_H

#include <thread.h>
#include <blocking_queue.h>
#include <thread_safe_queue.h>
#include <protocol/protocol_code.h>

#include <vector>
#include <mutex>

class VideoRecordThread : public Thread {
private:
    bool isDead;
    int width;
    int height;
    BlockingQueue<std::vector<char>> & videoFramesQueue;
    ThreadSafeQueue<ThreadStatus> & stopQueue;
    std::mutex mutex;

    /*Detiene la ejecucion del hilo*/
    void _stop();

public:
    /*
    PRE: Recibe: 
        las dimensiones del video : ancho y alto (int);
        una cola bloqueante por donde recibir los frames de 
        video a escribir en disco.
        una cola segura por donde comicarle a hilo principal 
        que termino de ejecutar por cierto motivo.
    POST: 
    */
    VideoRecordThread(
        int videoWidth,
        int videoHeight,
        BlockingQueue<std::vector<char>> & videoFramesQueue,
        ThreadSafeQueue<ThreadStatus> & stopQueue
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

#endif // VIDEO_RECORD_THREAD_H
