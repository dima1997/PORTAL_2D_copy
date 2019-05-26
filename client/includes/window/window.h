#ifndef WINDOW_H
#define WINDOW_H

#include "../textures/common_texture/big_texture.h"
#include "../textures/common_texture/texture.h"
//#include "../textures/static_texture/static_texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector> 
#include <string>
#include <cstdint>
#include <memory>

class Window {
private:
    int width;
    int height;
    uint32_t idMainTexture;
    //int widthEquivalent;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::map<std::string, BigTexture> bigTextures;
    std::vector<uint32_t> ids;
    std::map<uint32_t, std::unique_ptr<Texture>> allTextures;
    
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
        La longitud de la ventana equivalente en la medida en que
        se ubican y dimensionan los objetos son representados en la 
        misma.
    POST: Inicializa una ventana de las medidas recibidas.
    Levanta SDLException en caso de error.
    */
    //Window(int width, int height, int widthEquivalent);
    
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
    PRE: Recibe:
        El id (uint32_t) de la textura a agregar.
        Una ruta (const std::string &) a una gran imagen que contiene el sprite
        de que utilizara la textura estatica a agregar.
        Un area (Area) con las coordenadas y dimensiones del sprite a usar de 
        la gran imagen (en pixeles).
        Un area (Area) con las coordenadas y dimensiones del objeto que 
        representa la textura en el mapa de juego (en la unidad del largo 
        equivalente de la ventanta).
    POST: Agrega un nueva textura estatica a la ventana, bajo las condiciones 
    anteriores.
    */
    /*
    void add_static_texture(uint32_t id, 
                            const std::string & pathImage, 
                            Area areaSprite,
                            Area areaMap);
    */

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
    PRE: Recibe un identificador de una textura movible, 
    y nuevas coordenadas (float) x,y a donde desplazar la 
    textura.
    POST: Mueve la textura indicada en las coordenadas 
    recibidas.
    Levanta OSException en caso de error. 
    */
    void move_texture(uint32_t id, float x, float y);

    /*
    Devuelve una referencia constante al area (const Area &) 
    de la textura de Chell principal de la ventana.
    */
    const Area getMainTextureArea();

};

#endif // WINDOW_H