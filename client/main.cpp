#include "src/tests/animation_tests.h"
#include "src/common_texture/sdl_exception.h"
#include "src/window/os_exception.h"

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
        //testAnimateChellRunning();
        testAnimateChellJumping();
    } catch (SdlException &error){
        std::cout << error.what() << "\n";
        return 1;
    } catch (OSException &error){
        std::cout << error.what() << "\n";
        return 2;
    } catch (std::exception &error){
        std::cout << error.what() << "\n";
        return 3;
    }
    return 0;
}
