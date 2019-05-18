#include "animation_tests.h"

#include "window.h"
#include "area.h"

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
    window.add_static_texture(IMAGE_BLOCK_PATH, areaSprite, areaMap);
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
        window.add_static_texture(IMAGE_BLOCK_PATH, areaSprite, areaMap);
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
        window.add_static_texture(IMAGE_BLOCK_PATH, areaSprite, areaMap);
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
    //Techo
    for (int i = 0; i < manyBlocksHorizontal; ++i){
        float xCoord = i * blockSideMeters;
        float yCoord = 0; //Techo 
        Area areaMap(xCoord, yCoord, blockSideMeters, blockSideMeters);
        window.add_static_texture(IMAGE_BLOCK_PATH, areaSprite, areaMap);
    }
    //Izquierda
    for (int i = 1; i < manyBlocksVertical; ++i){ //Techo y piso ya estan
        float xCoord = 0;
        float yCoord = i * blockSideMeters; 
        Area areaMap(xCoord, yCoord, blockSideMeters, blockSideMeters);
        window.add_static_texture(IMAGE_BLOCK_PATH, areaSprite, areaMap);
    }
    //Derecha
    for (int i = 1; i < manyBlocksVertical; ++i){ //Techo y piso ya estan
        float xCoord = windowWidthMeters - blockSideMeters;
        float yCoord = i * blockSideMeters; 
        Area areaMap(xCoord, yCoord, blockSideMeters, blockSideMeters);
        window.add_static_texture(IMAGE_BLOCK_PATH, areaSprite, areaMap);
    }
    //Piso
    for (int i = 0; i < manyBlocksHorizontal; ++i){
        float xCoord = i * blockSideMeters;
        float yCoord = manyBlocksVertical * blockSideMeters; //Piso
        Area areaMap(xCoord, yCoord, blockSideMeters, blockSideMeters);
        window.add_static_texture(IMAGE_BLOCK_PATH, areaSprite, areaMap);
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
    window.add_static_texture(IMAGE_BLOCK_PATH, areaSprite, areaMap);
    window.render();
    SDL_Delay(SLEEP);
}