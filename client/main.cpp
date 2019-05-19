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
        testShowChell();
    } catch (SdlException &error){
        std::cout << error.what() << "\n";
        return 1;
    } catch (std::exception &error){
        std::cout << error.what() << "\n";
        return 2;
    }
    return 0;
}
/*
#0  0x0000000000403883 in BigTexture::render (this=0x0, src=..., dest=..., 
    flip=NO_FLIP)
    at /home/soporte/Documentos/Fiuba/cuatrimestre_actual/a_taller_1/tp_final/TP4_TALLER/client/src/big_texture.cpp:92
#1  0x00000000004056ef in MoveSense::render (this=0x229a900, bigTexture=..., 
    src=..., dest=...)
    at /home/soporte/Documentos/Fiuba/cuatrimestre_actual/a_taller_1/tp_final/TP4_TALLER/client/src/move_sense.cpp:41
#2  0x0000000000404e64 in ChellTexture::render (this=0x229a8f0, adjuster=64)
    at /home/soporte/Documentos/Fiuba/cuatrimestre_actual/a_taller_1/tp_final/TP4_TALLER/client/src/chell_texture.cpp:51
#3  0x0000000000405f2e in Window::render (this=0x7fffffffdb40)
    at /home/soporte/Documentos/Fiuba/cuatrimestre_actual/a_taller_1/tp_final/TP4_TALLER/client/src/window.cpp:72
#4  0x000000000040318b in testShowChell ()
    at /home/soporte/Documentos/Fiuba/cuatrimestre_actual/a_taller_1/tp_final/TP4_TALLER/client/src/animation_tests.cpp:193
#5  0x00000000004018cb in main (argc=1, argv=0x7fffffffdd18)
    at /home/soporte/Documentos/Fiuba/cuatrimestre_actual/a_taller_1/tp_final/TP4_TALLER/client/main.cpp:14

*/