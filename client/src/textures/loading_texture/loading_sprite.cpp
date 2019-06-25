#include "../../../includes/textures/loading_texture/loading_sprite.h"

#include "../../../includes/textures/common_texture/dynamic_sprite.h"

#include <vector>

/*
Devuelve un sprite dinamico de partida cargando.
IMAGE_PATH : LOADING_SPRITES
*/
DynamicSprite LoadingSprite::get_sprite(){
    int width = 395;
    int height = 395;
    int manySpritesHorizontal = 5;
    int manySpritesVertical = 4;
    std::vector<std::pair<int,int>> coords;
    int xBegin = 3 - (width + 5);
    int yBegin = 6 - (height + 5);
    int xNow = xBegin;
    int yNow = yBegin;
    for (int i = 0; i < manySpritesVertical; ++i){
        yNow = yNow + (height + 5);
        for (int k = 0; k < manySpritesHorizontal; ++k){
            xNow = xNow + (width + 5);
            coords.push_back(std::pair<int,int>(xNow,yNow));
        } 
        xNow = xBegin;
    }
    return DynamicSprite(coords,width,height);
}
