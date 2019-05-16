#include "src/window.h"

#include <SDL2/SDL.h>

#define WIDTH_SCREEN 680
#define HEIGHT_SCREEN 480

#define PATH_IMAGE "all_blocks.png"
#define X_IMAGE 1
#define Y_IMAGE 21
#define WIDTH_IMAGE 129
#define HEIGHT_IMAGE 130


void testShowOneBlock(){
    Window window(680, 480);
    window.fill();
    window.add_static_texture(PATH_IMAGE, X_IMAGE, Y_IMAGE, WIDTH_IMAGE, HEIGHT_IMAGE, WIDTH_SCREEN/2, HEIGHT_SCREEN/2);
    window.render();
    SDL_Delay(3000);
}

void testShowThreeBlocks(){
    Window window(680, 480);
    window.fill();
    window.add_static_texture(PATH_IMAGE, X_IMAGE, Y_IMAGE, WIDTH_IMAGE, HEIGHT_IMAGE, WIDTH_SCREEN/2 - WIDTH_IMAGE, HEIGHT_SCREEN/2);
    window.add_static_texture(PATH_IMAGE, X_IMAGE, Y_IMAGE, WIDTH_IMAGE, HEIGHT_IMAGE, WIDTH_SCREEN/2, HEIGHT_SCREEN/2);
    window.add_static_texture(PATH_IMAGE, X_IMAGE, Y_IMAGE, WIDTH_IMAGE, HEIGHT_IMAGE, WIDTH_SCREEN/2 + WIDTH_IMAGE, HEIGHT_SCREEN/2);
    // TODO : Arreglar espaciado por redimension 
    window.render();
    SDL_Delay(3000);
}

int main(int argc, char **argv) {
    //testShowOneBlock();
    testShowThreeBlocks();
    return 0;
}
