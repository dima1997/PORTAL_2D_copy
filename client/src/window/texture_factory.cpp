#include "../../includes/window/texture_factory.h"

#include "../../includes/window/window.h"
#include "../../includes/window/os_exception.h"
#include "../../includes/textures/common_texture/big_texture.h"
#include "../../includes/textures/common_texture/texture.h"
#include "../../includes/textures/common_texture/sprite_strategy.h"
#include "../../includes/textures/common_texture/sdl_exception.h"
#include "../../includes/textures/common_texture/images_paths.h"
#include "../../includes/textures/chell_texture/chell_texture.h"
#include "../../includes/textures/block_metal_texture/block_metal_sprite.h"
#include "../../includes/textures/block_rock_texture/block_rock_sprite.h"
#include "../../includes/textures/block_acid_texture/block_acid_sprite.h"
#include "../../includes/textures/portal_texture/portal_texture.h"
#include "../../includes/textures/door_texture/door_one_sprite_strategy.h"
#include "../../includes/textures/energy_ball_texture/energy_ball_sprite.h"
#include "../../includes/textures/button_texture/button_sprite_strategy.h"
#include "../../includes/textures/rock_texture/rock_sprite.h"
#include "../../includes/textures/barrier_texture/barrier_sprite.h"
#include "../../includes/textures/triangle_texture/triangle_botom_left_sprite.h"
#include "../../includes/textures/receiver_texture/receiver_sprite_strategy.h"
#include "../../includes/textures/emitter_texture/emitter_right_sprite.h"
#include "../../includes/textures/cake_texture/cake_sprite.h"
#include "../../includes/textures/background_texture/background_one_sprite.h"
#include "../../includes/textures/record_texture/record_texture.h"
#include "../../includes/textures/pin_tool_texture/pin_tool_sprite.h"

#include <memory>

/*
PRE: Recibe una ventana (Window & window) 
donde se renderizan las texturas.
POST: Inicializa una fabrica de texturas.
*/
TextureFactory::TextureFactory(){}

/*Destruye la fabrica de texturas.*/
TextureFactory::~TextureFactory() = default;

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de un bloque de metal.
*/
std::unique_ptr<Texture> TextureFactory::
create_block_metal(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_BLOCKS_SPRITES,
        areaMap,
        BlockMetalSprite::get_sprite,
        0,
        redMod,
        greenMod,
        blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de un bloque de roca.
*/
std::unique_ptr<Texture> TextureFactory::
create_block_rock(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_BLOCKS_SPRITES,
        areaMap,
        BlockRockSprite::get_sprite,
        0,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de bloque acido.
*/
std::unique_ptr<Texture> TextureFactory::
create_block_acid(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_BLOCKS_SPRITES,
        areaMap,
        BlockAcidSprite::get_sprite,
        0,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de Chell.
*/
std::unique_ptr<Texture> TextureFactory::
create_chell(
    Window & window, 
    Area & areaMap,
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    BigTexture & bigTexture = window.add_big_texture(
                                    IMAGES_PATHS.at(ALL_CHELL_SPRITES)
                                );
    std::unique_ptr<Texture> ptrTexture(new ChellTexture(
        bigTexture, 
        areaMap,
        redMod,
        greenMod,
        blueMod
    ));
    return std::move(ptrTexture);
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de portal azul.
*/
std::unique_ptr<Texture> TextureFactory::
create_portal_blue(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    BigTexture & bigTexture = window.add_big_texture(
                                    IMAGES_PATHS.at(PORTAL_SPRITES)
                                );
    std::unique_ptr<Texture> ptrTexture(new PortalTexture(
        bigTexture, 
        areaMap,
        1, 100, 255
    )); 
    return std::move(ptrTexture);
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de portal naranja.
*/
std::unique_ptr<Texture> TextureFactory::
create_portal_orange(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    BigTexture & bigTexture = window.add_big_texture(
                                    IMAGES_PATHS.at(PORTAL_SPRITES)
                                );
    std::unique_ptr<Texture> ptrTexture(new PortalTexture(
        bigTexture, 
        areaMap,
        255, 100, 1
    )); 
    return std::move(ptrTexture);
}


/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de puerta con numero 1.
*/
std::unique_ptr<Texture> TextureFactory::
create_door_one(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    BigTexture & bigTexture = window.add_big_texture(
                                    IMAGES_PATHS.at(ALL_DOORS_SPRITES)
                                );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        std::move(std::unique_ptr<SpriteStrategy>(
            new DoorOneSpriteStrategy()
        )),
        0,
        redMod, greenMod, blueMod
    ));   
    return std::move(ptrTexture);
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de boton.
*/
std::unique_ptr<Texture> TextureFactory::
create_button(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    BigTexture & bigTexture = window.add_big_texture(
                                    IMAGES_PATHS.at(BUTTON_SPRITES)
                                );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        std::move(std::unique_ptr<SpriteStrategy>(
            new ButtonSpriteStrategy()
        )),
        0,
        redMod, greenMod, blueMod
    ));   
    return std::move(ptrTexture);
}


/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de bola de energia verde.
*/
std::unique_ptr<Texture> TextureFactory::
create_energy_ball_green(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_ROCKS_AND_BALLS_SPRITES,
        areaMap,
        EnergyBallSprite::get_sprite,
        0,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de roca.
*/
std::unique_ptr<Texture> TextureFactory::
create_rock_one(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_ROCKS_AND_BALLS_SPRITES,
        areaMap,
        RockSprite::rock_one,
        0,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de roca.
*/
std::unique_ptr<Texture> TextureFactory::
create_rock_two(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_ROCKS_AND_BALLS_SPRITES,
        areaMap,
        RockSprite::rock_two,
        0,
        redMod, greenMod, blueMod
    ));
}
/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de roca.
*/
std::unique_ptr<Texture> TextureFactory::
create_rock_three(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_ROCKS_AND_BALLS_SPRITES,
        areaMap,
        RockSprite::rock_three,
        0,
        redMod, greenMod, blueMod
    ));
}
/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de roca.
*/
std::unique_ptr<Texture> TextureFactory::
create_rock_four(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_ROCKS_AND_BALLS_SPRITES,
        areaMap,
        RockSprite::rock_four,
        0,
        redMod, greenMod, blueMod
    ));
}
/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de roca.
*/
std::unique_ptr<Texture> TextureFactory::
create_rock_five(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_ROCKS_AND_BALLS_SPRITES,
        areaMap,
        RockSprite::rock_five,
        0,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de roca.
*/
std::unique_ptr<Texture> TextureFactory::
create_rock_six(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_ROCKS_AND_BALLS_SPRITES,
        areaMap,
        RockSprite::rock_six,
        0,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de roca.
*/
std::unique_ptr<Texture> TextureFactory::
create_rock_seven(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_ROCKS_AND_BALLS_SPRITES,
        areaMap,
        RockSprite::rock_seven,
        0,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de roca.
*/
std::unique_ptr<Texture> TextureFactory::
create_rock_eight(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_ROCKS_AND_BALLS_SPRITES,
        areaMap,
        RockSprite::rock_eight,
        0,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de barrera.
*/
std::unique_ptr<Texture> TextureFactory::
create_barrier(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        BARRIER_SPRITE,
        areaMap,
        BarrierSprite::get_sprite,
        0,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de trinagulo de esquina 
inferior izquierda.
*/
std::unique_ptr<Texture> TextureFactory::
create_triangle_botom_left(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_BLOCKS_SPRITES,
        areaMap,
        TriangleBotomLeftSprite::get_sprite,
        0,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de trinagulo de esquina 
inferior derecha.
*/
std::unique_ptr<Texture> TextureFactory::
create_triangle_botom_right(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_BLOCKS_SPRITES,
        areaMap,
        TriangleBotomLeftSprite::get_sprite,
        270,
        redMod, greenMod, blueMod
    ));
}
/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de trinagulo de esquina 
superior izquierda.
*/
std::unique_ptr<Texture> TextureFactory::
create_triangle_top_left(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_BLOCKS_SPRITES,
        areaMap,
        TriangleBotomLeftSprite::get_sprite,
        90,
        redMod, greenMod, blueMod
    ));
}
/*
PRE: Recibe el area (Area) donde se 
ubicara la textura.
POST: Devuelve un puntero unico a una 
textura(std::unique_ptr<Texture>), 
de la textura de trinagulo de esquina 
superior derecha.
*/
std::unique_ptr<Texture> TextureFactory::
create_triangle_top_right(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_BLOCKS_SPRITES,
        areaMap,
        TriangleBotomLeftSprite::get_sprite,
        180,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde se ubicara 
la textura.
POST: Devuelve un puntero unico a una 
textura(std::unique_ptr<Texture>), 
de la textura recibidor.
*/
std::unique_ptr<Texture> TextureFactory::
create_receiver(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    BigTexture & bigTexture = window.add_big_texture(
                                    IMAGES_PATHS.at(ALL_BLOCKS_SPRITES)
                                );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        std::move(std::unique_ptr<SpriteStrategy>(
            new ReceiverSpriteStrategy()
        )),
        0,
        redMod, greenMod, blueMod
    ));
    return std::move(ptrTexture);
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de emisor hacia derecha.
*/
std::unique_ptr<Texture> TextureFactory::
create_emitter_right(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_BLOCKS_SPRITES,
        areaMap,
        EmitterRightSprite::get_sprite,
        0,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de emisor hacia abajo.
*/
std::unique_ptr<Texture> TextureFactory::
create_emitter_down(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_BLOCKS_SPRITES,
        areaMap,
        EmitterRightSprite::get_sprite,
        90,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de emisor hacia izquierda.
*/
std::unique_ptr<Texture> TextureFactory::
create_emitter_left(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_BLOCKS_SPRITES,
        areaMap,
        EmitterRightSprite::get_sprite,
        180,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de emisor hacia arriba.
*/
std::unique_ptr<Texture> TextureFactory::
create_emitter_up(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        ALL_BLOCKS_SPRITES,
        areaMap,
        EmitterRightSprite::get_sprite,
        270,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de torta.
*/
std::unique_ptr<Texture> TextureFactory::
create_cake(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        CAKE_SPRITES,
        areaMap,
        CakeSprite::get_sprite,
        0,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de un bloque de metal.
*/
std::unique_ptr<Texture> TextureFactory::
create_background(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        BACKGROUND_SPRITES,
        areaMap,
        BackgroundOneSprite::get_sprite,
        0,
        redMod, greenMod, blueMod
    ));
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de un icono grabador de 
video.
*/
std::unique_ptr<Texture> TextureFactory::
create_record(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    BigTexture & bigTexture = window.add_big_texture(
                                    IMAGES_PATHS.at(ALL_BLOCKS_SPRITES)
                                );
    std::unique_ptr<Texture> ptrTexture(new RecordTexture(
        bigTexture, 
        areaMap
    ));
    return std::move(ptrTexture);
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de una pin tool.
*/
std::unique_ptr<Texture> TextureFactory::
create_pin_tool(
    Window & window, 
    Area & areaMap,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
)
{
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        PIN_TOOL_SPRITES,
        areaMap,
        PinToolSprite::get_sprite,
        0,
        redMod, greenMod, blueMod
    ));
}

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
std::unique_ptr<Texture> TextureFactory::
create_texture_one_sprite(
    Window & window,
    IMAGE_PATH imagePath, 
    Area & areaMap,
    DynamicSprite (&sprite_creator)()
) {
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        imagePath, 
        areaMap, 
        sprite_creator,
        0,
        255, 255, 255
    ));
}

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
std::unique_ptr<Texture> TextureFactory::
create_texture_one_sprite(
    Window & window,
    IMAGE_PATH imagePath, 
    Area & areaMap,
    DynamicSprite (&sprite_creator)(),
    double angle
) {
    return std::move(TextureFactory::create_texture_one_sprite(
        window,
        imagePath, 
        areaMap, 
        sprite_creator,
        angle,
        255, 255, 255
    ));
}

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
std::unique_ptr<Texture> TextureFactory::
create_texture_one_sprite(
    Window & window,
    IMAGE_PATH imagePath, 
    Area & areaMap,
    DynamicSprite (&sprite_creator)(),
    double angle,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod
) {
    BigTexture & bigTexture = window.add_big_texture(
                                IMAGES_PATHS.at(imagePath)
                              );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        sprite_creator(),
        angle,
        redMod,
        greenMod, 
        blueMod
    ));
    return std::move(ptrTexture);
}