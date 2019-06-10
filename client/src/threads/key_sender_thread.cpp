#include "../../includes/threads/key_sender_thread.h"

#include <thread.h>
#include <connector/connector.h>
#include <connector/socket_exception.h>
#include <protocol/protocol_code.h>
#include <blocking_queue.h>
#include <protocol/game_action/game_action.h>
#include <iostream>

/*
PRE: Recibe una referencia a un conector (Connector &),
ya conectado con el servidor del juego.
POST: Inicializa un hilo enviador de acciones del usuario 
sobre objetos del juego.
*/
KeySenderThread::KeySenderThread(
                Connector & connector, 
                BlockingQueue<std::unique_ptr<GameAction>> & actionsBlockQueue,
                ThreadSafeQueue<ThreadStatus> & stopQueue)
:   isDead(true), 
    connector(connector), 
    actionsBlockQueue(actionsBlockQueue),
    stopQueue(stopQueue),
    mutex() {}

/*
Destruye un hilo enviador de acciones 
del usuario sobre objetos del juego.
*/
KeySenderThread::~KeySenderThread() = default;

/*
Ejecuta un hilo enviador de acciones del usuario 
sobre objetos del juego.
Recibe acciones de los objetos del juego desde cola 
con que se inicializo, y los envia al servidor del 
juego.
*/
void KeySenderThread::run(){
    this->isDead = false;
    try {
        while (! this->is_dead()){
            std::unique_ptr<GameAction> ptrAction;
            if (! this->actionsBlockQueue.pop(ptrAction)){
                break;
            }
            GameAction & action = *(ptrAction);
            this->connector << action;
        }
        this->stop();
    } catch (SocketException &except){
        this->stop();
        std::cout << "Connection Lost at KS.\n";
        ThreadStatus stop = THREAD_STOP;
        this->stopQueue.push(stop);
        return;
    }
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
