#ifndef WINDOW_H
#define WINDOW_H

#include "../textures/common_texture/big_texture.h"
#include "../textures/common_texture/texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector> 
#include <string>
#include <cstdint>
#include <memory>
#include <mutex>

class Window {
private:
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
    bool isFullScreen;
    /*
    PRE: Recibe la ruta (const std::string &) de un gran textura 
    (imagen con varios sprites en ella).
    POST: Agrega la gran textura a la ventana, si que no se fue 
    ya agregada.
    Levanta SdlException en caso de error.
    */
    void add_big_texture(const std::string & pathImage);

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
    void add_map();

public:
    /*
    PRE: Recibe:
        La longitud y altura del ventanta en pixeles (ambos int).
        El id de la textura en la que se centrara e indicarara que mostrar 
        en la ventana.
    POST: Inicializa una ventana de las medidas recibidas.
    Levanta SDLException en caso de error.
    */
    Window(int width, int height, uint32_t idMainTexture);

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
    PRE: Recibe :
        El id (uint32_t) de indentificacion del bloque de metal a agregar.
        El area (Area) con las coordenadas y dimensiones del objeto
        que representa la textura en el mapa de juego (en unidades de 
        distancia del juego).
    POST: Agrega un nueva textura de bloque de metal a la ventana, bajo las 
    condiciones anteriores.
    Levanta SdlException en caso de error.
    */
    void add_block_metal_texture(uint32_t id, Area areaMap);

    /*
    PRE: Recibe :
        El id (uint32_t) de indentificacion de la chell a agregar.
        El area (Area) con las coordenadas y dimensiones del objeto
        que representa la textura en el mapa de juego (en unidades 
        de distancia del juego).
    POST: Agrega un nueva textura de bloque de metal a la ventana, 
    bajo las condiciones anteriores.
    Levanta SdlException en caso de error.
    */
    void add_chell_texture(uint32_t id, Area areaMap);

    /*
    PRE: Recibe :
        El id (uint32_t) de indentificacion del portal a agregar.
        El area (Area) con las coordenadas y dimensiones del objeto
        que representa la textura en el mapa de juego (en unidades de 
        distancia del juego).
    POST: Agrega un nueva textura de portal azul a la ventana, bajo las 
    condiciones anteriores.
    Levanta OSException o SdlException en caso de error.
    */
    void add_portal_texture(uint32_t id, Area areaMap);

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
};

#endif // WINDOW_H
