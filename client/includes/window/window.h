#ifndef WINDOW_H
#define WINDOW_H

#include "../textures/common_texture/big_texture.h"
#include "../textures/common_texture/texture.h"
#include "../mixer/mixer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <yaml-cpp/yaml.h>

#include <map>
#include <vector> 
#include <string>
#include <cstdint>
#include <memory>
#include <mutex>

class Window {
public:
    int width;
    int height;
    uint32_t idMainTexture;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::map<std::string, BigTexture> bigTextures;
    std::vector<uint32_t> ids;
    std::map<uint32_t, std::unique_ptr<Texture>> allTextures;
    Area areaCamera;
    std::mutex mutex;
    /*
    PRE: Recibe la ruta (const std::string &) de un gran textura 
    (imagen con varios sprites en ella).
    POST: Agrega la gran textura a la ventana, si que no se fue 
    ya agregada.
    Levanta SdlException en caso de error.
    */
    BigTexture & add_big_texture(const std::string & pathImage);

    /*
    PRE: Recibe el id de la textura a agregar.
    POST: Agrega la textura al la ventana.
    Levanta OSError si el id recibdo ya fue previamente agregado.
    */
    void add_id_texture(uint32_t id);

    /*
    PRE: Recibe el id (uint32_t) de la textura a agregar, y un puntero
    unico a textura (std::unique_ptr<Texture>) de la textura a agregar.
    POST: Agrega la textura recibida.
    */
    void add_texture(uint32_t id, std::unique_ptr<Texture> ptrTexture);
    
    /*
    Agrega el mapa de juego inicial, con todas sus texturas.
    Levanta SdlError o OSError en caso de error.
    */
    //void add_map();

public:
    /*
    PRE: Recibe:
        La longitud y altura del ventanta en pixeles (ambos int).
        El id de la textura en la que se centrara e indicarara que mostrar 
        en la ventana.
        La configuracion del mapa de juego (YAML::Node &).
    POST: Inicializa una ventana de las medidas recibidas.
    Levanta SDLException en caso de error.
    */
    Window(int width, int height, uint32_t idMainTexture, 
           YAML::Node & mapConfig);

    /*Destruye la ventana.*/
    ~Window();

    /*
    PRE: Recibe un color descripto en coordenadas RGB 
    (los tres int); y un valor de opacidad (int).
    POST: Pinta la ventana del color recibido.
    */
    void fill(int r, int g, int b, int alpha);

    /*Pinta a la ventana de color gris*/
    void fill();

    /*
    Renderiza todas las texturas que se agregaron a la ventana, 
    en el orden en que fueron agregadas; y por la ultimo la ventana 
    en si.
    */
    void render();

    /*
    PRE: Recibe un identificador de una textura movible, 
    y nuevas coordenadas (float) x,y a donde desplazar la 
    textura.
    POST: Mueve la textura indicada en las coordenadas 
    recibidas.
    Levanta OSException en caso de error. 
    */
    void move_texture(uint32_t id, float x, float y);

    /*
    PRE: Recibe un identificador (uint32_t) de una textura.
    POST: Switchea el sprite de la textura.
    Levanta OSException en caso de error. 
    */
    void switch_texture(uint32_t id);

    /*
    Devuelve una referencia constante al area (const Area &) 
    de la textura de Chell principal de la ventana.
    */
    const Area getMainTextureArea();

    /*
    PRE: Recibe las coordenadas x,y (int) en pixeles 
    de algun punto en la ventana.
    POST: Devuelve las coordenadas x,y (float) de dicho 
    punto en el mapa de juego. 
    */
    std::tuple<float,float> getMapCoords(int x, int y);

    /*
    Reproduce los sonidos de todas 
    las textura de la ventana.
    */
    void sound(Mixer & mixer);

    /*
    PRE: Recibe el id (uint32_t) de dos texturas en la ventana.
    POST: Hace que la primera (idFollowing) se ponga a seguir 
    a la segunda (idFollowed).
    */
    void start_follow(uint32_t idFollowing, uint32_t idFollowed);

    /*
    PRE: Recibe el id de una textura en la ventana.
    POST: Hace que la textura deje de seguir a cualquier
    otra textura que este siguiendo.
    */
    void stop_follow(uint32_t idFollowing);
};

#endif // WINDOW_H
