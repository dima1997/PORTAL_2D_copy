#include "src/animation_tests.h"
#include "src/sdl_exception.h"

#include <iostream>
#include <exception> 

int main(int argc, char **argv) {
    try {
        //testShowOneBlock();
        //testShowThreeBlocks();
        //testShowGroundOfBlocks();
        //testShowFrameOfBlocks();
        //testShowPartOfBlockFarBeferoOrigin();
        //testShowChell();
        //testAnimateChellSweat();
        testAnimateChellRunning();
    } catch (SdlException &error){
        std::cout << error.what() << "\n";
        return 1;
    } catch (std::exception &error){
        std::cout << error.what() << "\n";
        return 2;
    }
    return 0;
}
