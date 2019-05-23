#include "includes/tests/animation_tests.h"
#include "includes/textures/common_texture/sdl_exception.h"
#include "includes/window/os_exception.h"

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
        //testAnimateChellJumping();
        testAnimationLoopKeyReader();
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
