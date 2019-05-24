#include "../../includes/tests/animation_tests.h"

#include "../../includes/window/window.h"
#include "../../includes/textures/common_texture/area.h"
#include "../../includes/threads/animation_loop_thread.h"
#include "../../includes/threads/key_reader_thread.h"
#include "../../includes/threads/game_proxy_thread.h"

#include "../../../common/thread_safe_queue.h"

#include <map>

#include <SDL2/SDL.h>

#define WIDTH_WINDOW 640
#define HEIGHT_WINDOW 480

#define IMAGE_BLOCK_PATH "all_blocks.png"
#define IMAGE_BLOCK_X 1
#define IMAGE_BLOCK_Y 21
#define IMAGE_BLOCK_WIDTH 129
#define IMAGE_BLOCK_HEIGHT 130

#define WINDOW_WIDTH_METERS_STD 10
#define BLOCK_SIDE_METERS_STD 1

#define SLEEP 3000

/*
Muetra la textura de un bloque, 
con coordenada superior izquierda, 
en el centro de la ventana.
*/
void testShowOneBlock(){
    int windowWidthPixels = WIDTH_WINDOW;
    int windowHeightPixels = HEIGHT_WINDOW;
    float windowWidthMeters = WINDOW_WIDTH_METERS_STD;
    float windowHeightMeters = windowHeightPixels * (windowWidthMeters/windowWidthPixels);
    float blockSideMeters = BLOCK_SIDE_METERS_STD;
    Window window(windowWidthPixels, windowHeightPixels, windowWidthMeters);
    window.fill();
    Area areaSprite(IMAGE_BLOCK_X, IMAGE_BLOCK_Y, IMAGE_BLOCK_WIDTH, IMAGE_BLOCK_HEIGHT);
    float xCoord = windowWidthMeters/(float)2;
    float yCoord = windowHeightMeters/(float)2;
    Area areaMap(xCoord, yCoord, blockSideMeters, blockSideMeters);
    window.add_static_texture(0,IMAGE_BLOCK_PATH, areaSprite, areaMap);
    window.render();
    SDL_Delay(SLEEP);
}

/*
Muetra las texturas de 3 bloques,
con coordenadas superiores izquierda,
en el centro de la ventana, uno al lado 
del otro (sin solaparse).
*/
void testShowThreeBlocks(){
    int windowWidthPixels = WIDTH_WINDOW;
    int windowHeightPixels = HEIGHT_WINDOW;
    float windowWidthMeters = WINDOW_WIDTH_METERS_STD;
    float windowHeightMeters = windowHeightPixels * (windowWidthMeters/windowWidthPixels);
    float blockSideMeters = BLOCK_SIDE_METERS_STD;
    Window window(windowWidthPixels, windowHeightPixels, windowWidthMeters);
    window.fill();
    Area areaSprite(IMAGE_BLOCK_X, IMAGE_BLOCK_Y, IMAGE_BLOCK_WIDTH, IMAGE_BLOCK_HEIGHT);
    for (int i = -1; i < 2; ++i){
        float xCoord = windowWidthMeters/(float)2 + (i * blockSideMeters);
        float yCoord = windowHeightMeters/(float)2;
        Area areaMap(xCoord,yCoord,blockSideMeters,blockSideMeters);
        window.add_static_texture(i+1,IMAGE_BLOCK_PATH, areaSprite, areaMap);
    }
    window.render();
    SDL_Delay(SLEEP);
}

/*
Muetra todo el borde inferior de la 
ventana cubierto de texturas de bloque.
(Los bloques no deben solaparse)
*/
void testShowGroundOfBlocks(){
    int windowWidthPixels = WIDTH_WINDOW;
    int windowHeightPixels = HEIGHT_WINDOW;
    float windowWidthMeters = WINDOW_WIDTH_METERS_STD;
    float windowHeightMeters = windowHeightPixels * (windowWidthMeters/windowWidthPixels);
    float blockSideMeters = BLOCK_SIDE_METERS_STD;
    Window window(windowWidthPixels, windowHeightPixels, windowWidthMeters);
    window.fill();
    int manyBlocks = windowWidthMeters / blockSideMeters;
    Area areaSprite(IMAGE_BLOCK_X, IMAGE_BLOCK_Y, IMAGE_BLOCK_WIDTH, IMAGE_BLOCK_HEIGHT);
    for (int i = 0; i < manyBlocks; ++i){
        float xCoord = i * blockSideMeters;
        float yCoord = windowHeightMeters - blockSideMeters; 
        Area areaMap(xCoord, yCoord, blockSideMeters, blockSideMeters);
        window.add_static_texture(i,IMAGE_BLOCK_PATH, areaSprite, areaMap);
    }
    window.render();
    SDL_Delay(SLEEP);
}

/*
Muetra todo el marco de la ventana 
cubierta de texturas de bloques.
(Los bloques no deben solaparse)
Los bloques en el borde inferior 
pueden quedar cortados, y eso esta 
bien.
*/
void testShowFrameOfBlocks(){
    int windowWidthPixels = WIDTH_WINDOW;
    int windowHeightPixels = HEIGHT_WINDOW;
    float windowWidthMeters = WINDOW_WIDTH_METERS_STD;
    float windowHeightMeters = windowHeightPixels * (windowWidthMeters/windowWidthPixels);
    float blockSideMeters = BLOCK_SIDE_METERS_STD;
    Window window(windowWidthPixels, windowHeightPixels, windowWidthMeters);
    window.fill();
    int manyBlocksHorizontal = windowWidthMeters / blockSideMeters;
    int manyBlocksVertical = windowHeightMeters / blockSideMeters;
    Area areaSprite(IMAGE_BLOCK_X, IMAGE_BLOCK_Y, IMAGE_BLOCK_WIDTH, IMAGE_BLOCK_HEIGHT);
    uint32_t id = 0;
    //Techo
    for (int i = 0; i < manyBlocksHorizontal; ++i){
        float xCoord = i * blockSideMeters;
        float yCoord = 0; //Techo 
        Area areaMap(xCoord, yCoord, blockSideMeters, blockSideMeters);
        window.add_static_texture(id,IMAGE_BLOCK_PATH, areaSprite, areaMap);
        ++id;
    }
    //Izquierda
    for (int i = 1; i < manyBlocksVertical; ++i){ //Techo y piso ya estan
        float xCoord = 0;
        float yCoord = i * blockSideMeters; 
        Area areaMap(xCoord, yCoord, blockSideMeters, blockSideMeters);
        window.add_static_texture(id,IMAGE_BLOCK_PATH, areaSprite, areaMap);
        ++id;
    }
    //Derecha
    for (int i = 1; i < manyBlocksVertical; ++i){ //Techo y piso ya estan
        float xCoord = windowWidthMeters - blockSideMeters;
        float yCoord = i * blockSideMeters; 
        Area areaMap(xCoord, yCoord, blockSideMeters, blockSideMeters);
        window.add_static_texture(id,IMAGE_BLOCK_PATH, areaSprite, areaMap);
        ++id;
    }
    //Piso
    for (int i = 0; i < manyBlocksHorizontal; ++i){
        float xCoord = i * blockSideMeters;
        float yCoord = manyBlocksVertical * blockSideMeters; //Piso
        Area areaMap(xCoord, yCoord, blockSideMeters, blockSideMeters);
        window.add_static_texture(id,IMAGE_BLOCK_PATH, areaSprite, areaMap);
        ++id;
    }
    window.render();
    SDL_Delay(SLEEP);
}

/*
Muetra una textura de bloque, 
con coordenada superior izquierda,
anterior al 0,0, correspondiente a
la esquina superior izquierda de la 
ventana.
Solo se debe ver la seccion del bloque 
que cuyas coordenadas son superior al 
origen de la ventana.
*/
void testShowPartOfBlockFarBeferoOrigin(){
    int windowWidthPixels = WIDTH_WINDOW;
    int windowHeightPixels = HEIGHT_WINDOW;
    float windowWidthMeters = WINDOW_WIDTH_METERS_STD;
    float windowHeightMeters = windowHeightPixels * (windowWidthMeters/windowWidthPixels);
    float blockSideMeters = windowWidthMeters;
    Window window(windowWidthPixels, windowHeightPixels, windowWidthMeters);
    window.fill();
    int manyBlocksHorizontal = windowWidthMeters / blockSideMeters;
    int manyBlocksVertical = windowHeightMeters / blockSideMeters;
    Area areaSprite(IMAGE_BLOCK_X, IMAGE_BLOCK_Y, IMAGE_BLOCK_WIDTH, IMAGE_BLOCK_HEIGHT);
    Area areaMap(- blockSideMeters/2, - blockSideMeters/2, blockSideMeters, blockSideMeters);
    window.add_static_texture(0,IMAGE_BLOCK_PATH, areaSprite, areaMap);
    window.render();
    SDL_Delay(SLEEP);
}

/*
Muetra una chell en el centro de la ventana.
*/
void testShowChell(){
    int windowWidthPixels = WIDTH_WINDOW;
    int windowHeightPixels = HEIGHT_WINDOW;
    float windowWidthMeters = 5;
    float windowHeightMeters = windowHeightPixels * (windowWidthMeters/windowWidthPixels);
    float chellWidthMeters = 1;
    float chellHeightMeters = 1.5;
    float chellXCoord = windowWidthMeters/2;
    float chellYCoord = windowHeightMeters/2;
    Area areaMap(chellXCoord, chellYCoord, chellWidthMeters, chellHeightMeters);
    Window window(windowWidthPixels, windowHeightPixels, windowWidthMeters);
    window.fill();
    window.add_chell_texture(0,areaMap);
    window.render();
    SDL_Delay(SLEEP);
}

/*
Muestra una chell sudando
*/
void testAnimateChellSweat(){
    int windowWidthPixels = WIDTH_WINDOW;
    int windowHeightPixels = HEIGHT_WINDOW;
    float windowWidthMeters = 5;
    float windowHeightMeters = windowHeightPixels * (windowWidthMeters/windowWidthPixels);
    float chellWidthMeters = 1;
    float chellHeightMeters = 1.5;
    float chellXCoord = windowWidthMeters/2;
    float chellYCoord = windowHeightMeters/2;
    Area areaMap(chellXCoord, chellYCoord, chellWidthMeters, chellHeightMeters);
    Window window(windowWidthPixels, windowHeightPixels, windowWidthMeters);
    window.add_chell_texture(0,areaMap);
    bool quit = false;
    SDL_Event event;
    unsigned t0, t1;
    double maxSleepMS = 75;
    while( !quit ){
        //Handle events on queue
        while( SDL_PollEvent( &event ) != 0 )
        {
            //User requests quit
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        window.fill();

        t0=clock();
        window.render();
        t1 = clock();
        double timeSeconds = (double(t1-t0)/CLOCKS_PER_SEC);
        double timeMiliSeconds = timeSeconds * 1000;
        SDL_Delay(maxSleepMS - timeMiliSeconds);
    }
}

/*
Muestra a Chell desplazandose de hacia derecha y deteniendose.
*/
void testAnimateChellRunning(){
    int windowWidthPixels = WIDTH_WINDOW;
    int windowHeightPixels = HEIGHT_WINDOW;
    float windowWidthMeters = 5;
    float windowHeightMeters = windowHeightPixels * (windowWidthMeters/windowWidthPixels);
    float chellWidthMeters = 1;
    float chellHeightMeters = 1.5;
    float chellXCoord = windowWidthMeters/2;
    float chellYCoord = windowHeightMeters/2;
    Area areaMap(chellXCoord, chellYCoord, chellWidthMeters, chellHeightMeters);
    uint32_t idChell = 0;
    float chellMetersPerFrame = 0.2;
    Window window(windowWidthPixels, windowHeightPixels, windowWidthMeters);
    window.add_chell_texture(idChell,areaMap);
    bool quit = false;
    SDL_Event event;
    unsigned t0, t1;
    double maxSleepMS = 75;
    while( !quit ){
        //Handle events on queue
        while( SDL_PollEvent( &event ) != 0 ){
            switch(event.type) {
                case SDL_KEYDOWN: {
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                    switch (keyEvent.keysym.sym) {
                        case SDLK_LEFT:
                            chellXCoord -= chellMetersPerFrame;
                            window.move_texture(idChell,chellXCoord, chellYCoord);
                            break;
                        case SDLK_RIGHT:
                            chellXCoord += chellMetersPerFrame;
                            window.move_texture(idChell,chellXCoord, chellYCoord);
                            break;
                        }
                    } // Fin KEY_DOWN
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
        window.fill();
        t0=clock();
        window.render();
        t1 = clock();
        double timeSeconds = (double(t1-t0)/CLOCKS_PER_SEC);
        double timeMiliSeconds = timeSeconds * 1000;
        SDL_Delay(maxSleepMS - timeMiliSeconds);
    }
}

/*
Muestra a Chell saltando verticalmente y hacia la derecha.
*/
void testAnimateChellJumping(){
    int windowWidthPixels = WIDTH_WINDOW;
    int windowHeightPixels = HEIGHT_WINDOW;
    float windowWidthMeters = 5;
    float windowHeightMeters = windowHeightPixels * (windowWidthMeters/windowWidthPixels);
    float chellWidthMeters = 1;
    float chellHeightMeters = 1.5;
    float chellXCoord = 0;
    float chellYCoord = windowHeightMeters - chellHeightMeters;
    Area areaMap(chellXCoord, chellYCoord, chellWidthMeters, chellHeightMeters);
    uint32_t idChell = 0;
    float chellMetersPerFrame = 0.1;
    Window window(windowWidthPixels, windowHeightPixels, windowWidthMeters);
    window.add_chell_texture(idChell,areaMap);
    unsigned t0, t1;
    std::vector<std::pair<float,float>> moves;
    int manyJumps = 20;
    int i = 0;
    for (; i < manyJumps; ++i){
        moves.push_back({chellXCoord, chellYCoord - i*chellMetersPerFrame});
    }
    for (; i >= 0; --i){
        moves.push_back({chellXCoord, chellYCoord - i*chellMetersPerFrame});
    }
    for (i = 0; i < manyJumps/2; ++i){
        moves.push_back({chellXCoord + i*chellMetersPerFrame, chellYCoord - i*chellMetersPerFrame});
    }
    for (i; i < manyJumps; ++i){
        moves.push_back({chellXCoord + i*chellMetersPerFrame, chellYCoord - (manyJumps - i)*chellMetersPerFrame});
    }
    float animationTimeMS = 2000; //miliSeconds
    float miliSecondsPerFrame = animationTimeMS/moves.size(); 
    for (int i = 0; i < moves.size(); ++i){
        window.move_texture(idChell, moves[i].first, moves[i].second);
        t0=clock();
        window.fill();
        window.render();
        t1 = clock();
        double timeSeconds = (double(t1-t0)/CLOCKS_PER_SEC);
        double timeMiliSeconds = timeSeconds * 1000;
        SDL_Delay(miliSecondsPerFrame - timeMiliSeconds);
    }
    t0=clock();
    window.fill();
    window.render();
    t1 = clock();
    double timeSeconds = (double(t1-t0)/CLOCKS_PER_SEC);
    double timeMiliSeconds = timeSeconds * 1000;
    SDL_Delay(miliSecondsPerFrame - timeMiliSeconds);
}

/*
Ejecuta la animacion de chell sudando, renderizandola desde el 
AnimationLoopThread; y controlando la entrada del usuario a traves
del KeyReaderThread. 
(En este caso , la entrada del usuario es solo cerrar la ventana)
*/
void testAnimationLoopKeyReader(){
    TSQueueChangesMade_t changesMade;
    TSQueueChangesAsk_t changesAsk;
    int windowWidthPixels = WIDTH_WINDOW;
    int windowHeightPixels = HEIGHT_WINDOW;
    float windowWidthMeters = 5;
    float windowHeightMeters = windowHeightPixels * (windowWidthMeters/windowWidthPixels);
    float chellWidthMeters = 1;
    float chellHeightMeters = 1.5;
    float chellXCoord = windowWidthMeters/2;
    float chellYCoord = windowHeightMeters/2;
    Area areaMap(chellXCoord, chellYCoord, chellWidthMeters, chellHeightMeters);
    uint32_t idChell = 0;
    Window window(windowWidthPixels, windowHeightPixels, windowWidthMeters);
    window.add_chell_texture(idChell,areaMap);
    std::map<uint32_t,Area> gameMap({{idChell,areaMap}});
    GameProxyThread game(gameMap, changesMade, changesAsk);
    AnimationLoopThread animationLoop(window, changesMade);
    KeyReaderThread keyReader(idChell,changesAsk);
    game.start();
    animationLoop.start(); //Ejecuto hilo
    keyReader.run(); // No ejecuto hilo separado, corre sobre hilo actual.
    animationLoop.stop();
    animationLoop.join();
    game.stop();
    game.join();
}