#include "../../../includes/textures/chell_texture/chell_dying_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

#include <vector>

/*
Devuelve un sprite dinamico de Chell mueriendo.
Este sprite dinamico corresponde a una serie de 
sprites de la imagen ALL_CHELL_SPRITES, de 
images_path.h.
*/
DynamicSprite ChellDyingSprite::get_sprite(){
    int width = 175;
    int height = 261;
    std::vector<std::pair<int,int>> coords;
    int xBegin = 2 - (width + 1);
    int xBefore = xBegin;
    int yBefore = 3224 - (height + 1);
    int xNow;
    int yNow;
    for (int i = 0; i < 8; ++i){
        yNow = yBefore + (height + 1);
        yBefore = yNow;
        for (int k = 0; k < 9; ++k){
            xNow = xBefore + (width + 1);
            xBefore = xNow;
            coords.push_back(std::pair<int,int>(xNow,yNow));
        } 
        xBefore = xBegin;
    }
    return std::move(DynamicSprite(coords,width,height));
}
