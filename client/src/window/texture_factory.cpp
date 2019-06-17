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
#include "../../includes/textures/portal_texture/portal_blue_texture.h"
#include "../../includes/textures/portal_texture/portal_orange_texture.h"
#include "../../includes/textures/door_texture/door_one_sprite_strategy.h"
#include "../../includes/textures/energy_ball_texture/energy_ball_sprite.h"
#include "../../includes/textures/button_texture/button_sprite_strategy.h"
#include "../../includes/textures/rock_texture/rock_one_sprite.h"
#include "../../includes/textures/barrier_texture/barrier_sprite.h"
#include "../../includes/textures/triangle_texture/triangle_botom_left_sprite.h"
#include "../../includes/textures/triangle_texture/triangle_botom_right_sprite.h"
#include "../../includes/textures/triangle_texture/triangle_top_left_sprite.h"
#include "../../includes/textures/triangle_texture/triangle_top_right_sprite.h"
#include "../../includes/textures/receiver_texture/receiver_sprite_strategy.h"
#include "../../includes/textures/emitter_texture/emitter_right_sprite.h"
#include "../../includes/textures/cake_texture/cake_sprite.h"
#include "../../includes/textures/background_texture/background_one_sprite.h"
#include "../../includes/textures/record_texture/record_texture.h"

#include <memory>

/*
PRE: Recibe una ventana (Window & window) 
donde se renderizan las texturas.
POST: Inicializa una fabrica de texturas.
*/
TextureFactory::TextureFactory(Window & window)
:   window(window) {}

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
create_block_metal(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    ALL_BLOCKS_SPRITES
                                );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        BlockMetalSprite::get_sprite()
    ));
    return std::move(ptrTexture);
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de un bloque de roca.
*/
std::unique_ptr<Texture> TextureFactory::
create_block_rock(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    ALL_BLOCKS_SPRITES
                                );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        BlockRockSprite::get_sprite()
    ));
    return std::move(ptrTexture);
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de Chell.
*/
std::unique_ptr<Texture> TextureFactory::
create_chell(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    ALL_CHELL_SPRITES
                                );
    std::unique_ptr<Texture> ptrTexture(new ChellTexture(
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
de la textura de portal azul.
*/
std::unique_ptr<Texture> TextureFactory::
create_portal_blue(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    PORTAL_SPRITES
                                );
    std::unique_ptr<Texture> ptrTexture(new PortalBlueTexture(
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
de la textura de portal naranja.
*/
std::unique_ptr<Texture> TextureFactory::
create_portal_orange(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    PORTAL_SPRITES
                                );
    std::unique_ptr<Texture> ptrTexture(new PortalOrangeTexture(
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
de la textura de puerta con numero 1.
*/
std::unique_ptr<Texture> TextureFactory::
create_door_one(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    ALL_DOORS_SPRITES
                                );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        std::move(std::unique_ptr<SpriteStrategy>(
            new DoorOneSpriteStrategy()
        ))
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
create_button(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    BUTTON_SPRITE
                                );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        std::move(std::unique_ptr<SpriteStrategy>(
            new ButtonSpriteStrategy()
        ))
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
create_energy_ball_green(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    ALL_ROCKS_AND_BALLS_SPRITES
                                );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        EnergyBallSprite::get_sprite()
    ));
    return std::move(ptrTexture);
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de roca.
*/
std::unique_ptr<Texture> TextureFactory::
create_rock_one(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    ALL_ROCKS_AND_BALLS_SPRITES
                                );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        RockOneSprite::get_sprite()
    )); 
    return std::move(ptrTexture);
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de barrera.
*/
std::unique_ptr<Texture> TextureFactory::
create_barrier(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    BARRIER_SPRITE
                                );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        BarrierSprite::get_sprite()
    ));
    return std::move(ptrTexture);
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
create_triangle_botom_left(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    ALL_TRIANGLES_SPRITES
                                );
    std::unique_ptr<Texture> ptrTexture(
        new Texture(
            bigTexture, 
            areaMap,
            TriangleBotomLeftSprite::get_sprite()
        )
    );   
    return std::move(ptrTexture);
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
create_triangle_botom_right(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    ALL_TRIANGLES_SPRITES
                                );
    std::unique_ptr<Texture> ptrTexture(
        new Texture(
            bigTexture, 
            areaMap,
            TriangleBotomRightSprite::get_sprite()
        )
    );  
    return std::move(ptrTexture);
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
create_triangle_top_left(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    ALL_TRIANGLES_SPRITES
                                ); 
    std::unique_ptr<Texture> ptrTexture(
        new Texture(
            bigTexture, 
            areaMap,
            TriangleTopLeftSprite::get_sprite()
        )
    ); 
    return std::move(ptrTexture);
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
create_triangle_top_right(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    ALL_TRIANGLES_SPRITES
                                );
    std::unique_ptr<Texture> ptrTexture(
        new Texture(
            bigTexture, 
            areaMap,
            TriangleTopRightSprite::get_sprite()
        )
    );   
    return std::move(ptrTexture);
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de bloque acido.
*/
std::unique_ptr<Texture> TextureFactory::
create_block_acid(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    ALL_BLOCKS_SPRITES
                                );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        BlockAcidSprite::get_sprite()
    ));  
    return std::move(ptrTexture);
}

/*
PRE: Recibe el area (Area) donde se ubicara 
la textura.
POST: Devuelve un puntero unico a una 
textura(std::unique_ptr<Texture>), 
de la textura recibidor.
*/
std::unique_ptr<Texture> TextureFactory::
create_receiver(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    ALL_BLOCKS_SPRITES
                                );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        std::move(std::unique_ptr<SpriteStrategy>(
            new ReceiverSpriteStrategy()
        ))
    ));
    return std::move(ptrTexture);
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de emisor.
*/
std::unique_ptr<Texture> TextureFactory::
create_emitter_right(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    ALL_BLOCKS_SPRITES
                                );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        EmitterRightSprite::get_sprite()
    ));
    return std::move(ptrTexture);
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de torta.
*/
std::unique_ptr<Texture> TextureFactory::
create_cake(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    CAKE_SPRITES
                                );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        CakeSprite::get_sprite()
    ));
    return std::move(ptrTexture);
}

/*
PRE: Recibe el area (Area) donde 
se ubicara la textura.
POST: Devuelve un puntero unico 
a una textura(std::unique_ptr<Texture>), 
de la textura de un bloque de metal.
*/
std::unique_ptr<Texture> TextureFactory::
create_background(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    BACKGROUND
                                );
    std::unique_ptr<Texture> ptrTexture(new Texture(
        bigTexture, 
        areaMap,
        BackgroundOneSprite::get_sprite()
    ));
    return std::move(ptrTexture);
}

std::unique_ptr<Texture> TextureFactory::
create_record(Area areaMap){
    BigTexture & bigTexture = this->window.add_big_texture(
                                    RECORD
                                );
    std::unique_ptr<Texture> ptrTexture(new RecordTexture(
        bigTexture, 
        areaMap
    ));
    return std::move(ptrTexture);
}