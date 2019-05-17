#include "src/window.h"
#include "src/area.h"

#include <SDL2/SDL.h>

#define WIDTH_WINDOW 640
#define HEIGHT_WINDOW 480

#define PATH_IMAGE "all_blocks.png"
#define X_IMAGE 1
#define Y_IMAGE 21
#define WIDTH_IMAGE 129
#define HEIGHT_IMAGE 130

#define METERS_EQ_WIDTH_WINDOW 10
#define METERS_EQ_SIDE_BLOCK 1

#define SLEEP 5000

void testShowOneBlock(){
    float adjuster = WIDTH_WINDOW/METERS_EQ_WIDTH_WINDOW; 
    Window window(WIDTH_WINDOW, HEIGHT_WINDOW, METERS_EQ_WIDTH_WINDOW);
    window.fill();
    Area areaSprite(X_IMAGE, Y_IMAGE, WIDTH_IMAGE, HEIGHT_IMAGE);
    float xCoord = METERS_EQ_WIDTH_WINDOW/(float)2;
    float yCoord = (HEIGHT_WINDOW/adjuster)/(float)2;
    Area areaMap(xCoord, yCoord, METERS_EQ_SIDE_BLOCK, METERS_EQ_SIDE_BLOCK);
    window.add_static_texture(PATH_IMAGE, areaSprite, areaMap);
    window.render();
    SDL_Delay(SLEEP);
}

void testShowThreeBlocks(){
    float adjuster = WIDTH_WINDOW/METERS_EQ_WIDTH_WINDOW; 
    Window window(WIDTH_WINDOW, HEIGHT_WINDOW, METERS_EQ_WIDTH_WINDOW);
    window.fill();
    Area areaSprite(X_IMAGE, Y_IMAGE, WIDTH_IMAGE, HEIGHT_IMAGE);
    float xCoord = METERS_EQ_WIDTH_WINDOW/(float)2;
    float yCoord = (HEIGHT_WINDOW/adjuster)/(float)2;
    Area areaMapLeft(xCoord - METERS_EQ_SIDE_BLOCK, yCoord, METERS_EQ_SIDE_BLOCK, METERS_EQ_SIDE_BLOCK);
    Area areaMapCenter(xCoord, yCoord, METERS_EQ_SIDE_BLOCK, METERS_EQ_SIDE_BLOCK);
    Area areaMapRight(xCoord + METERS_EQ_SIDE_BLOCK, yCoord, METERS_EQ_SIDE_BLOCK, METERS_EQ_SIDE_BLOCK);
    window.add_static_texture(PATH_IMAGE, areaSprite, areaMapLeft);
    window.add_static_texture(PATH_IMAGE, areaSprite, areaMapCenter);
    window.add_static_texture(PATH_IMAGE, areaSprite, areaMapRight);
    window.render();
    SDL_Delay(SLEEP);
}

void testShowGroundOfBlocks(){
    int windowWidthPixels = WIDTH_WINDOW;
    int windowHeightPixels = HEIGHT_WINDOW;
    float windowWidthMeters = 10;
    float windowHeightMeters = windowHeightPixels * (windowWidthMeters/windowWidthPixels);
    Window window(windowWidthPixels, windowHeightPixels, windowWidthMeters);
    window.fill();
    float blockSideMeters = 1;
    int manyBlocks = windowWidthMeters / blockSideMeters;
    Area areaSprite(X_IMAGE, Y_IMAGE, WIDTH_IMAGE, HEIGHT_IMAGE);
    for (int i = 0; i < manyBlocks; ++i){
        float xCoord = i * blockSideMeters;
        float yCoord = windowHeightMeters - blockSideMeters; 
        Area areaMap(xCoord, yCoord, blockSideMeters, blockSideMeters);
        window.add_static_texture(PATH_IMAGE, areaSprite, areaMap);
    }
    window.render();
    SDL_Delay(SLEEP);
}

void testShowFrameOfBlocks(){
    int windowWidthPixels = WIDTH_WINDOW;
    int windowHeightPixels = HEIGHT_WINDOW;
    float windowWidthMeters = 10;
    float windowHeightMeters = windowHeightPixels * (windowWidthMeters/windowWidthPixels);
    Window window(windowWidthPixels, windowHeightPixels, windowWidthMeters);
    window.fill();
    float blockSideMeters = 1;
    int manyBlocksHorizontal = windowWidthMeters / blockSideMeters;
    int manyBlocksVertical = windowHeightMeters / blockSideMeters;
    Area areaSprite(X_IMAGE, Y_IMAGE, WIDTH_IMAGE, HEIGHT_IMAGE);
    //Techo
    for (int i = 0; i < manyBlocksHorizontal; ++i){
        float xCoord = i * blockSideMeters;
        float yCoord = 0; //Techo 
        Area areaMap(xCoord, yCoord, blockSideMeters, blockSideMeters);
        window.add_static_texture(PATH_IMAGE, areaSprite, areaMap);
    }
    //Izquierda
    for (int i = 1; i < manyBlocksVertical; ++i){ //Techo y piso ya estan
        float xCoord = 0;
        float yCoord = i * blockSideMeters; 
        Area areaMap(xCoord, yCoord, blockSideMeters, blockSideMeters);
        window.add_static_texture(PATH_IMAGE, areaSprite, areaMap);
    }
    //Derecha
    for (int i = 1; i < manyBlocksVertical; ++i){ //Techo y piso ya estan
        float xCoord = windowWidthMeters - blockSideMeters;
        float yCoord = i * blockSideMeters; 
        Area areaMap(xCoord, yCoord, blockSideMeters, blockSideMeters);
        window.add_static_texture(PATH_IMAGE, areaSprite, areaMap);
    }
    //Piso
    for (int i = 0; i < manyBlocksHorizontal; ++i){
        float xCoord = i * blockSideMeters;
        float yCoord = manyBlocksVertical * blockSideMeters; 
        Area areaMap(xCoord, yCoord, blockSideMeters, blockSideMeters);
        window.add_static_texture(PATH_IMAGE, areaSprite, areaMap);
    }
    window.render();
    SDL_Delay(SLEEP);
}

void testShowPartOfBlockFarBeferoOrigin(){
    int windowWidthPixels = WIDTH_WINDOW;
    int windowHeightPixels = HEIGHT_WINDOW;
    float windowWidthMeters = 10;
    float windowHeightMeters = windowHeightPixels * (windowWidthMeters/windowWidthPixels);
    Window window(windowWidthPixels, windowHeightPixels, windowWidthMeters);
    window.fill();
    float blockSideMeters = windowWidthMeters;
    int manyBlocksHorizontal = windowWidthMeters / blockSideMeters;
    int manyBlocksVertical = windowHeightMeters / blockSideMeters;
    Area areaSprite(X_IMAGE, Y_IMAGE, WIDTH_IMAGE, HEIGHT_IMAGE);
    Area areaMap(-blockSideMeters/2,-blockSideMeters/2,blockSideMeters,blockSideMeters);
    window.add_static_texture(PATH_IMAGE, areaSprite, areaMap);
    window.render();
    SDL_Delay(SLEEP);
}

int main(int argc, char **argv) {
    //testShowOneBlock();
    //testShowThreeBlocks();
    //testShowGroundOfBlocks();
    //testShowFrameOfBlocks();
    testShowPartOfBlockFarBeferoOrigin();
    return 0;
}