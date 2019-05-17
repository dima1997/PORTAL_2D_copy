#include "src/window.h"
#include "src/area.h"

#include <SDL2/SDL.h>

#define WIDTH_WINDOW 680
#define HEIGHT_WINDOW 480

#define PATH_IMAGE "all_blocks.png"
#define X_IMAGE 1
#define Y_IMAGE 21
#define WIDTH_IMAGE 129
#define HEIGHT_IMAGE 130

#define METERS_EQ_WIDTH_WINDOW 4
#define METERS_EQ_SIDE_BLOCK 1

#define SLEEP 5000

void testShowOneBlock(){
    float adjuster = WIDTH_WINDOW/METERS_EQ_WIDTH_WINDOW; 
    Window window(WIDTH_WINDOW, HEIGHT_WINDOW, METERS_EQ_WIDTH_WINDOW);
    window.fill();
    Area areaSprite(X_IMAGE, Y_IMAGE, WIDTH_IMAGE, HEIGHT_IMAGE);
    int xCoord = METERS_EQ_WIDTH_WINDOW/2;
    int yCoord = (HEIGHT_WINDOW/adjuster)/2;
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
    int xCoord = METERS_EQ_WIDTH_WINDOW/2;
    int yCoord = (HEIGHT_WINDOW/adjuster)/2;
    Area areaMapLeft(xCoord - METERS_EQ_SIDE_BLOCK, yCoord, METERS_EQ_SIDE_BLOCK, METERS_EQ_SIDE_BLOCK);
    Area areaMapCenter(xCoord, yCoord, METERS_EQ_SIDE_BLOCK, METERS_EQ_SIDE_BLOCK);
    Area areaMapRight(xCoord + METERS_EQ_SIDE_BLOCK, yCoord, METERS_EQ_SIDE_BLOCK, METERS_EQ_SIDE_BLOCK);
    window.add_static_texture(PATH_IMAGE, areaSprite, areaMapLeft);
    window.add_static_texture(PATH_IMAGE, areaSprite, areaMapCenter);
    window.add_static_texture(PATH_IMAGE, areaSprite, areaMapRight);
    window.render();
    SDL_Delay(SLEEP);
}

int main(int argc, char **argv) {
    testShowOneBlock();
    //testShowThreeBlocks();
    return 0;
}