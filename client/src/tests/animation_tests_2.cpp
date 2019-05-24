#include "../../includes/tests/animation_tests_2.h"

#include "../../includes/window/window.h"

#include "../../includes/textures/common_texture/area.h"

#include "../../includes/threads/animation_loop_thread.h"
#include "../../includes/threads/key_reader_thread.h"
#include "../../includes/threads/game_proxy_thread.h"

#include "../../../common/thread_safe_queue.h"

#include <map>

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

/*
Prueba 2.
*/
void testUserGameAnimationProxy(){
    TSQueueChangesMade_t changesMade;
    TSQueueChangesAsk_t changesAsk;
    int windowWidthPixels = WINDOW_WIDTH;
    int windowHeightPixels = WINDOW_HEIGHT;
    uint32_t idChell = 0;
    Window window(windowWidthPixels, windowHeightPixels, idChell);
    const Area & areaChell = window.getMainTextureArea();
    std::map<uint32_t,Area> gameMap({{idChell,areaChell}});
    GameProxyThread game(gameMap, changesMade, changesAsk);
    AnimationLoopThread animationLoop(window, changesMade);
    KeyReaderThread keyReader(idChell,changesAsk);
    game.start();
    animationLoop.start(); 
    keyReader.run(); 
    animationLoop.stop();
    animationLoop.join();
    game.stop();
    game.join();
}
