#ifndef TEXTURE_FACTORY_H
#define TEXTURE_FACTORY_H

#include <memory>
#include "window.h"
#include "../textures/common_texture/texture.h"
#include "../textures/common_texture/area.h"
#include "../textures/common_texture/images_paths.h"

class TextureFactory {
public:
    /*
    PRE: Recibe una ventana (Window & window) 
    donde se renderizan las texturas.
    POST: Inicializa una fabrica de texturas.
    */
    TextureFactory();
    
    /*Destruye la fabrica de texturas.*/
    ~TextureFactory();

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de un bloque de metal.
    */
    static std::unique_ptr<Texture> create_block_metal(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de un bloque de roca.
    */
    static std::unique_ptr<Texture> create_block_rock(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de bloque acido.
    */
    static std::unique_ptr<Texture> create_block_acid(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de Chell.
    */
    static std::unique_ptr<Texture> create_chell(
        Window & window, 
        Area & areaMap, 
        uint8_t redMod, 
        uint8_t greenMod, 
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de portal azul.
    */
    static std::unique_ptr<Texture> create_portal_blue(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de portal naranja.
    */
    static std::unique_ptr<Texture> create_portal_orange(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de puerta con numero 1.
    */
    static std::unique_ptr<Texture> create_door_one(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de boton.
    */
    static std::unique_ptr<Texture> create_button(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );


    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de bola de energia verde.
    */
    static std::unique_ptr<Texture> create_energy_ball_green(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de roca.
    */
    static std::unique_ptr<Texture> create_rock_one(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de roca.
    */
    static std::unique_ptr<Texture> create_rock_two(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de roca.
    */
    static std::unique_ptr<Texture> create_rock_three(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de roca.
    */
    static std::unique_ptr<Texture> create_rock_four(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de roca.
    */
    static std::unique_ptr<Texture> create_rock_five(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de roca.
    */
    static std::unique_ptr<Texture> create_rock_six(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de roca.
    */
    static std::unique_ptr<Texture> create_rock_seven(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de roca.
    */
    static std::unique_ptr<Texture> create_rock_eight(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de barrera.
    */
    static std::unique_ptr<Texture> create_barrier(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );
    
    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de trinagulo de esquina 
    inferior izquierda.
    */
    static std::unique_ptr<Texture> create_triangle_botom_left(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de trinagulo de esquina 
    inferior derecha.
    */
    static std::unique_ptr<Texture> create_triangle_botom_right(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de trinagulo de esquina 
    superior izquierda.
    */
    static std::unique_ptr<Texture> create_triangle_top_left(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde se 
    ubicara la textura.
    POST: Devuelve un puntero unico a una 
    textura(std::unique_ptr<Texture>), 
    de la textura de trinagulo de esquina 
    superior derecha.
    */
    static std::unique_ptr<Texture> create_triangle_top_right(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde se ubicara 
    la textura.
    POST: Devuelve un puntero unico a una 
    textura(std::unique_ptr<Texture>), 
    de la textura recibidor.
    */
    static std::unique_ptr<Texture> create_receiver(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de emisor hacia derecha.
    */
    static std::unique_ptr<Texture> create_emitter_right(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de emisor hacia abajo.
    */
    static std::unique_ptr<Texture> create_emitter_down(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de emisor hacia izquierda.
    */
    static std::unique_ptr<Texture> create_emitter_left(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de emisor hacia arriba.
    */
    static std::unique_ptr<Texture> create_emitter_up(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );
    
    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de torta.
    */
    static std::unique_ptr<Texture> create_cake(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de un bloque de metal.
    */
    static std::unique_ptr<Texture> create_background(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de un icono grabador de 
    video.
    */
    static std::unique_ptr<Texture> create_record(
        Window & window, 
        Area & areaMap,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );

    /*
    PRE: Recibe:
        la ruta de una gran imagen (IMAGES_PATH);
        el area (Area) del mapa de juego donde se ubica 
        inicialmente la textura;
        una funciona para crear un sprite dynamico 
        (DynamicSprite (&sprite_creator)());
    POST: Devuelve un puntero unico a una textura 
    (std::unique_ptr<Texture>) con las condiciones 
    anteriores.
    */
    static std::unique_ptr<Texture> create_texture_one_sprite(
        Window & window,
        IMAGE_PATH imagePath, 
        Area & areaMap, 
        DynamicSprite (&sprite_creator)()
    );

    /*
    PRE: Recibe:
        la ruta de una gran imagen (IMAGES_PATH);
        el area (Area) del mapa de juego donde se ubica 
        inicialmente la textura;
        una funciona para crear un sprite dynamico 
        (DynamicSprite (&sprite_creator)());
        un angulo para rotar la textura (double);
    POST: Devuelve un puntero unico a una textura 
    (std::unique_ptr<Texture>) con las condiciones 
    anteriores.
    */
    static std::unique_ptr<Texture> create_texture_one_sprite(
        Window & window,
        IMAGE_PATH imagePath, 
        Area & areaMap, 
        DynamicSprite (&sprite_creator)(),
        double angle
    );

    /*
    PRE: Recibe:
        la ruta de una gran imagen (IMAGES_PATH);
        el area (Area) del mapa de juego donde se ubica 
        inicialmente la textura;
        una funciona para crear un sprite dynamico 
        (DynamicSprite (&sprite_creator)());
        un angulo para rotar la textura (double);
        tres modificadores de colores RGB, uno para cada 
        uno respectivamente, para modularizar el color de
        la textura (uint8_t):  el colo se multiplica por 
        xMod/255
    POST: Devuelve un puntero unico a una textura 
    (std::unique_ptr<Texture>) con las condiciones 
    anteriores.
    */
    static std::unique_ptr<Texture> create_texture_one_sprite(
        Window & window,
        IMAGE_PATH imagePath, 
        Area & areaMap, 
        DynamicSprite (&sprite_creator)(),
        double angle,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );
};

#endif // TEXTURE_FACTORY_H
