#ifndef KEY_READER_THREAD_H
#define KEY_READER_THREAD_H

#include <thread.h>
#include <thread_safe_queue.h>

class KeyReaderThread : public Thread {
private:
    bool isDead;
    uint32_t idObject;
    TSQueueChangesAsk_t & changesAsk;
public:
    /*Inicializa un lector de eventos.*/
    KeyReaderThread(uint32_t idObject, TSQueueChangesAsk_t & changesAsk);
    // Faltaria que reciba el socket y el id de la textura que controla

    /*Destruye el lector de eventos.*/
    ~KeyReaderThread();

    /*Ejecuta el lector de eventos.*/
    void run();

    /*Detiene la ejecucion del hilo.*/
    void stop();

    /*
    Devuelve true si el hilo esta muerto; 
    false en caso contrario.
    */
    bool is_dead();

    /*
    Envia al juego la accion a realizar.
    */
    void send(gameObjectAction_t action);
    
};

#endif // KEY_READER_THREAD_H