#include "../../includes/threads/key_sender_thread.h"

#include "../../../common/thread.h"
#include "../../../common/connector.h"
#include "../../../common/protocol_code.h"
#include "../../../common/blocking_queue.h" 

/*
PRE: Recibe una referencia a un conector (Connector &),
ya conectado con el servidor del juego.
POST: Inicializa un hilo enviador de acciones del usuario 
sobre objetos del juego.
*/
KeySenderThread::KeySenderThread(Connector & connector, 
                    BlockingQueue<GameObjectAction> & actionsBlockQueue)
: connector(connector), actionsBlockQueue(actionsBlockQueue) {}

/*
Destruye un hilo enviador de acciones 
del usuario sobre objetos del juego.
*/
KeySenderThread::~KeySenderThread() = default;

/*
Ejecuta un hilo enviador de acciones 
del usuario sobre objetos del juego.
*/
void KeySenderThread::run(){
    while (! this.is_dead()){
        GameObjectAction action;
        if (! this->actionsBlockQueue.pop(action)){
            break;
        }
        uint8_t actionToSend = (uint8_t) action;
        this->connector << actionToSend;
    }
    this->stop();
}

/*Detiene la ejecucion del hilo.*/
void KeySenderThread::stop(){
    this->isDead = true;
}

/*
Devuelve true si el hilo esta muerto; 
false en caso contrario.
*/
bool KeySenderThread::is_dead(){
    return this->isDead;
}
