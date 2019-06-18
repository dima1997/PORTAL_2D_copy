#ifndef TEXTURE_FACTORY_H
#define TEXTURE_FACTORY_H

#include <memory>
#include "window.h"
#include "../textures/common_texture/texture.h"
#include "../textures/common_texture/area.h"
#include "../textures/common_texture/images_paths.h"

class TextureFactory {
private:
    Window & window;
public:
    /*
    PRE: Recibe una ventana (Window & window) 
    donde se renderizan las texturas.
    POST: Inicializa una fabrica de texturas.
    */
    TextureFactory(Window & window);

    /*Destruye la fabrica de texturas.*/
    ~TextureFactory();

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de un bloque de metal.
    */
    std::unique_ptr<Texture> create_block_metal(Area areaMap);


    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de un bloque de roca.
    */
    std::unique_ptr<Texture> create_block_rock(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de Chell.
    */
    std::unique_ptr<Texture> create_chell(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de portal azul.
    */
    std::unique_ptr<Texture> create_portal_blue(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de portal naranja.
    */
    std::unique_ptr<Texture> create_portal_orange(Area areaMap);


    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de puerta con numero 1.
    */
    std::unique_ptr<Texture> create_door_one(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de boton.
    */
    std::unique_ptr<Texture> create_button(Area areaMap);


    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de bola de energia verde.
    */
    std::unique_ptr<Texture> create_energy_ball_green(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de roca.
    */
    std::unique_ptr<Texture> create_rock_one(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de barrera.
    */
    std::unique_ptr<Texture> create_barrier(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de trinagulo de esquina 
    inferior izquierda.
    */
    std::unique_ptr<Texture> create_triangle_botom_left(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de trinagulo de esquina 
    inferior derecha.
    */
    std::unique_ptr<Texture> create_triangle_botom_right(Area areaMap);
    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de trinagulo de esquina 
    superior izquierda.
    */
    std::unique_ptr<Texture> create_triangle_top_left(Area areaMap);
    /*
    PRE: Recibe el area (Area) donde se 
    ubicara la textura.
    POST: Devuelve un puntero unico a una 
    textura(std::unique_ptr<Texture>), 
    de la textura de trinagulo de esquina 
    superior derecha.
    */
    std::unique_ptr<Texture> create_triangle_top_right(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de bloque acido.
    */
    std::unique_ptr<Texture> create_block_acid(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde se ubicara 
    la textura.
    POST: Devuelve un puntero unico a una 
    textura(std::unique_ptr<Texture>), 
    de la textura recibidor.
    */
    std::unique_ptr<Texture> create_receiver(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de emisor hacia derecha.
    */
    std::unique_ptr<Texture> create_emitter_right(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de emisor hacia abajo.
    */
    std::unique_ptr<Texture> create_emitter_down(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de emisor hacia izquierda.
    */
    std::unique_ptr<Texture> create_emitter_left(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de emisor hacia arriba.
    */
    std::unique_ptr<Texture> create_emitter_up(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de torta.
    */
    std::unique_ptr<Texture> create_cake(Area areaMap);
    
    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de un fondo de pantalla.
    */
    std::unique_ptr<Texture> create_background(Area areaMap);

    /*
    PRE: Recibe el area (Area) donde 
    se ubicara la textura.
    POST: Devuelve un puntero unico 
    a una textura(std::unique_ptr<Texture>), 
    de la textura de un icono grabador de 
    video.
    */
    std::unique_ptr<Texture> create_record(Area areaMap);

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
    std::unique_ptr<Texture> create_texture_one_sprite(
        IMAGE_PATH imagePath, 
        Area areaMap, 
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
        tres modificadores de colores RGB, uno para cada 
        uno respectivamente, para modularizar el color de
        la textura (uint8_t):  el colo se multiplica por 
        xMod/255
    POST: Devuelve un puntero unico a una textura 
    (std::unique_ptr<Texture>) con las condiciones 
    anteriores.
    */
    std::unique_ptr<Texture> create_texture_one_sprite(
        IMAGE_PATH imagePath, 
        Area areaMap, 
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
    std::unique_ptr<Texture> create_texture_one_sprite(
        IMAGE_PATH imagePath, 
        Area areaMap, 
        DynamicSprite (&sprite_creator)(),
        double angle,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod
    );
};

#endif // TEXTURE_FACTORY_H
