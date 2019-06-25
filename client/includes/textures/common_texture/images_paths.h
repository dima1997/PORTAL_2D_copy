#ifndef IMAGES_PATH_H
#define IMAGES_PATH_H

#include <map>
#include <string>

enum IMAGE_PATH{
    ALL_BLOCKS_SPRITES,
    ALL_CHELL_SPRITES,
    PORTAL_SPRITES,
    ALL_DOORS_SPRITES,
    ALL_ROCKS_AND_BALLS_SPRITES,
    BUTTON_SPRITES,
    BARRIER_SPRITE,
    ALL_TRIANGLES_SPRITES,
    CAKE_SPRITES,
    BACKGROUND_SPRITES,
    RECORD_SPRITES,
    PIN_TOOL_SPRITES,
    LOADING_SPRITES
};

const std::map<IMAGE_PATH,std::string> IMAGES_PATHS({
    std::pair<IMAGE_PATH,std::string>(ALL_BLOCKS_SPRITES, "only_blocks.png"),
    std::pair<IMAGE_PATH,std::string>(ALL_CHELL_SPRITES, "all_chells_half.png"), 
    std::pair<IMAGE_PATH,std::string>(PORTAL_SPRITES, "white_portal.png"),
    std::pair<IMAGE_PATH,std::string>(ALL_DOORS_SPRITES, "doors.png"),
    std::pair<IMAGE_PATH,std::string>(ALL_ROCKS_AND_BALLS_SPRITES, "balls_and_rocks.png"),
    std::pair<IMAGE_PATH,std::string>(BUTTON_SPRITES, "button_sprites.png"),
    std::pair<IMAGE_PATH,std::string>(BARRIER_SPRITE, "barrier.png"),
    std::pair<IMAGE_PATH,std::string>(ALL_TRIANGLES_SPRITES, "all_triangles.png"),
    std::pair<IMAGE_PATH,std::string>(CAKE_SPRITES, "cake.png"),
    std::pair<IMAGE_PATH,std::string>(BACKGROUND_SPRITES, "portal_background_3.jpg"),
    std::pair<IMAGE_PATH,std::string>(RECORD_SPRITES, "record_icons.png"),
    std::pair<IMAGE_PATH,std::string>(PIN_TOOL_SPRITES, "pin_tool.png"),
    std::pair<IMAGE_PATH,std::string>(LOADING_SPRITES, "loading_3.png")
});

#endif // IMAGES_PATH_H
