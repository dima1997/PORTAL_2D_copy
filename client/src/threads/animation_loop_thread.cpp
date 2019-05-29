#include "../../includes/threads/animation_loop_thread.h"

#include "../../includes/textures/common_texture/texture_move_change.h"
#include "../../includes/textures/common_texture/texture_switch_change.h"
#include "../../includes/window/window.h"
#include <protocol/event/event.h>
#include <protocol/protocol_code.h>

#include <thread.h>
#include <thread_safe_queue.h>
#include <protocol/event/object_moves_event.h>
#include <protocol/event/object_switch_event.h>

#include <SDL2/SDL.h>

#define TIME_WAIT_MICRO_SECONDS 70000
#define ONE_SECOND_EQ_MICRO_SECONDS 100000 

/*
PRE: Recibe un evento de sdl (SDL_Event &).
POST: Procesa el evento recibido. 
*/
void KeyReaderThread::process_event(SDL_Event & event){
    switch(event.type) {
        case SDL_KEYDOWN: {
            auto& keyEvent = (SDL_KeyboardEvent &) event;
            switch (keyEvent.keysym.sym) {
                case SDLK_LEFT:
                    this->push_action(move_left);
                    break;
                case SDLK_RIGHT:
                    this->push_action(move_right);
                    break;
                case SDLK_UP:
                    this->push_action(jump);
                    break;
            }
            break;
        }
        case SDL_QUIT:
            {
                GameActionName quitGame = quit_game;
                this->push_action(quitGame);
                this->stop();
                this->endQueue.push(quitGame);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            {
                auto& mouseEvent = (SDL_MouseButtonEvent &) event;
                int xWindow,yWindow;
                xWindow = mouseEvent.x;
                yWindow = mouseEvent.y;
                float xMap,yMap;
                std::tie(xMap,yMap) = this->window.getMapCoords(xWindow,yWindow);
                std::cout << "x map : " << xMap << " ;y map : " << yMap << "\n";
                switch (mouseEvent.button){
                    case SDL_BUTTON_LEFT:
                        {
                            std::unique_ptr<GameAction> ptrAction (
                                new CoordsAction(open_blue_portal,xMap,yMap)
                            );
                            this->gameActions.push(ptrAction);
                        }
                        break;
                    case SDL_BUTTON_RIGHT:
                        {
                            std::unique_ptr<GameAction> ptrAction (
                                new CoordsAction(open_orange_portal,xMap,yMap)
                            );
                            this->gameActions.push(ptrAction);   
                        }
                        break;
                }
            }
            break;

    }
} 
/*
PRE: Recibe el nombre de una accion del juego (GamaActionName).
POST: Encola en la cola de acciones del juego, la accion correspondiente
al nombre de accion recibido.
*/
void KeyReaderThread::push_action(GameActionName actionName){
    std::unique_ptr<GameAction> ptrGameAction(new GameAction(actionName));
    this->gameActions.push(ptrGameAction);
}

/*
PRE: Recibe donde ventana (Window &) donde se renderizan las texturas; 
y una cola bloqueante de cambios a realizar sobre las texturas de la 
ventana (TSQueueChangesMade_t &).
POST: Inicializa un loop de animaciones.
*/

AnimationLoopThread::AnimationLoopThread(Window &window, 
ThreadSafeQueue<std::unique_ptr<Event>> & changesMade)
: window(window), changesMade(changesMade), isDead(true) {}

/*
AnimationLoopThread::AnimationLoopThread(Window &window, 
ThreadSafeQueue<std::unique_ptr<TextureChange>> & changesMade)
: window(window), changesMade(changesMade), isDead(true) {}
*/
/*
Destruye el hilo: loop de animaciones. 
*/
AnimationLoopThread::~AnimationLoopThread(){
    this->stop();
}

/*
Ejecuta el hilo: loop de animaciones
*/
void AnimationLoopThread::run(){
    {
        std::unique_lock<std::mutex> l(this->mutex);
        this->isDead = false;
    }
    unsigned t0, t1, t2;
    double timeWaitMicroSeconds = TIME_WAIT_MICRO_SECONDS;
    while( ! this->is_dead() ){
        t0=clock();
        t2=clock();
        double timeProcessMicroSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        while (timeProcessMicroSeconds <= timeWaitMicroSeconds){
            std::unique_ptr<Event> ptrEvent;

            if (! this->changesMade.pop(ptrEvent)){
                break;
            }
            switch(ptrEvent->eventType){
                case object_moves:
                    {
                        auto ptrAux = static_cast<ObjectMovesEvent* >(ptrEvent.release());
                        std::unique_ptr<ObjectMovesEvent> ptrMovesEvent(ptrAux);
                        ObjectMovesEvent event = *(ptrMovesEvent);
                        TextureMoveChange textureChange(event);
                        textureChange.change(this->window);
                    }
                    break;
                case object_switch_state:
                    {
                        auto ptrAux = static_cast<ObjectSwitchEvent* >(ptrEvent.release());
                        std::unique_ptr<ObjectSwitchEvent> ptrSwitchEvent(ptrAux);
                        ObjectSwitchEvent event = *(ptrSwitchEvent);
                        TextureSwitchChange textureChange(event);
                        textureChange.change(this->window);
                    }
            }
            
            //ptrChange->change(this->window);
            t2=clock();
            timeProcessMicroSeconds = (double(t2-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        }
        window.fill();
        window.render();
        t1 = clock();
        double timeSpendMicroSeconds = (double(t1-t0)/CLOCKS_PER_SEC) * ONE_SECOND_EQ_MICRO_SECONDS;
        std::this_thread::sleep_for(std::chrono::microseconds((int)(timeWaitMicroSeconds - timeSpendMicroSeconds)));
    }
    this->stop();
}

/*
Detiene el hilo: loop de animaciones.
*/
void AnimationLoopThread::stop(){
    std::unique_lock<std::mutex> l(this->mutex);
    this->isDead = true;
}

/*
Devuelve true, si el hilo: loop de animaciones 
esta muerto; false en caso contrario.
*/
bool AnimationLoopThread::is_dead(){
    std::unique_lock<std::mutex> l(this->mutex);
    return this->isDead;
}
