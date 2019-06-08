#ifndef _MIX_CHUNCK_H_
#define _MIX_CHUNCK_H_

#include <SDL2/SDL_mixer.h>
#include <string>

class MixChunck {
private:
    Mix_Chunk * mixChunck;
public:
    /*
    PRE: Recibe una ruta a un trozo de sonido 
    de terminacion : .wav .
    POST: Inicializa un trozo de sonido.
    */
    MixChunck(std::string pathSound);

    /*Destruye el trozo de sonido.*/
    ~MixChunck();

    /*Construccion por movimiento.*/
    MixChunck(MixChunck && other);

    /*Asignacion por movimiento.*/
    MixChunck & operator=(MixChunck && other);

    MixChunck(const MixChunck & other) = delete;
    MixChunck & operator=(const MixChunck & other) = delete;

    /*Reproduce el trozo de sonido una sola vez.*/
    void play();
};

#endif // _MIX_CHUNNCK_H_
