#include "../../../includes/textures/chell_texture/chell_stand_right_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

#include <vector>

/*
Devuelve un sprite dinamico de Chell parada
(mirando hacia la derecha).
IMAGE_PATH : ALL_CHELL_SPRITES
*/
DynamicSprite ChellStandRightSprite::get_sprite(){
    int width = 104;
    int height = 215;
    std::vector<std::pair<int,int>> coords;
    int xBefore = 1 - (width + 1);
    int y = 2073;
    int xNow;
    for (int k = 0; k < 7; ++k){
        xNow = xBefore + (width + 1);
        xBefore = xNow;
        coords.push_back(std::pair<int,int>(xNow,y));
    } 
    return DynamicSprite(coords,width,height);
}
