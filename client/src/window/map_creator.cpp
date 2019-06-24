#include "../../includes/window/map_creator.h"

#include "../../includes/window/window.h"
#include "../../includes/window/os_exception.h"
#include "../../includes/window/texture_factory.h"
#include "../../includes/textures/common_texture/texture.h"

#include <configs_yaml/config_paths.h>
#include <cstdint>

typedef std::unique_ptr<Texture> (&texture_creator)(
    Window &, 
    Area &, 
    uint8_t, 
    uint8_t, 
    uint8_t
);

const std::map<std::string, texture_creator> ADD_TEXTURE_METHODS({
    std::pair<std::string, texture_creator>("blocks_metal",TextureFactory::create_block_metal), 
    std::pair<std::string, texture_creator>("blocks_rock",TextureFactory::create_block_rock),
    std::pair<std::string, texture_creator>("blocks_acid",TextureFactory::create_block_acid),
    std::pair<std::string, texture_creator>("portals_blue",TextureFactory::create_portal_blue),
    std::pair<std::string, texture_creator>("portals_orange",TextureFactory::create_portal_orange),
    std::pair<std::string, texture_creator>("doors_one",TextureFactory::create_door_one),
    std::pair<std::string, texture_creator>("buttons",TextureFactory::create_button),
    std::pair<std::string, texture_creator>("rocks_one",TextureFactory::create_rock_one),
    std::pair<std::string, texture_creator>("rocks_two",TextureFactory::create_rock_two),
    std::pair<std::string, texture_creator>("rocks_three",TextureFactory::create_rock_three),
    std::pair<std::string, texture_creator>("rocks_four",TextureFactory::create_rock_four),
    std::pair<std::string, texture_creator>("rocks_five",TextureFactory::create_rock_five),
    std::pair<std::string, texture_creator>("rocks_six",TextureFactory::create_rock_six),
    std::pair<std::string, texture_creator>("rocks_seven",TextureFactory::create_rock_seven),
    std::pair<std::string, texture_creator>("rocks_eight",TextureFactory::create_rock_eight),
    std::pair<std::string, texture_creator>("barriers",TextureFactory::create_barrier),
    std::pair<std::string, texture_creator>("energy_balls_green",TextureFactory::create_energy_ball_green),
    std::pair<std::string, texture_creator>("receivers",TextureFactory::create_receiver),
    std::pair<std::string, texture_creator>("emitters_right",TextureFactory::create_emitter_right),
    std::pair<std::string, texture_creator>("emitters_up",TextureFactory::create_emitter_up),
    std::pair<std::string, texture_creator>("emitters_left",TextureFactory::create_emitter_left),
    std::pair<std::string, texture_creator>("emitters_down",TextureFactory::create_emitter_down),
    std::pair<std::string, texture_creator>("triangles_botom_left",TextureFactory::create_triangle_botom_left),
    std::pair<std::string, texture_creator>("triangles_botom_right",TextureFactory::create_triangle_botom_right),
    std::pair<std::string, texture_creator>("triangles_top_left",TextureFactory::create_triangle_top_left),
    std::pair<std::string, texture_creator>("triangles_top_right",TextureFactory::create_triangle_top_right),
    std::pair<std::string, texture_creator>("cakes",TextureFactory::create_cake),
    std::pair<std::string, texture_creator>("chells",TextureFactory::create_chell),
    std::pair<std::string, texture_creator>("background",TextureFactory::create_background),
    std::pair<std::string, texture_creator>("records",TextureFactory::create_record),
    std::pair<std::string, texture_creator>("pin_tools",TextureFactory::create_pin_tool),
    std::pair<std::string, texture_creator>("loadings",TextureFactory::create_loading)
});


/*
PRE: Recibe el id (unt8_t) del mapa a crear, 
y la ventana (Window &) donde se agregaran 
las texturas del mapa.
POST: Inicializa un creador de mapa. 
*/
MapCreator::MapCreator(YAML::Node & gameConfig, Window & window)
:   window(window), baseNode(gameConfig) {}

/*Destruye el creador de mapa*/
MapCreator::~MapCreator() = default;

void MapCreator::add_texture(
    uint32_t id, 
    Area area,
    std::string & subSectionName
)
{
    this->add_texture(id, area, 255, 255, 255, subSectionName);
}

void MapCreator::add_texture(
    uint32_t id, 
    Area area,
    uint8_t redMod,
    uint8_t greenMod,
    uint8_t blueMod,
    std::string & subSectionName
)
{
    if (ADD_TEXTURE_METHODS.count(subSectionName) == 0){
        std::stringstream err;
        err << "MapCreator: There is not section map with name : ";
        err << subSectionName << "\n";
        throw OSException(err.str().c_str(),"");
    }
    texture_creator & textureCreator = ADD_TEXTURE_METHODS.at(subSectionName);
    this->window.add_texture(id, std::move(textureCreator(
        this->window,
        area, 
        redMod, 
        greenMod, 
        blueMod
    )));
    if (subSectionName == "records"){
        this->window.set_record_id(id);
    }
    if (subSectionName == "loadings"){
        this->window.set_loading_id(id);
    }
}

void MapCreator::add_multiple_sizes(std::string & subSectionName){
    YAML::Node subSectionNode = this->baseNode[subSectionName];
    for (int i = 0; i < (int)subSectionNode.size(); ++i){
        uint32_t id = subSectionNode[i]["id"].as<uint32_t>();  
        float width = subSectionNode[i]["width"].as<float>();
        float height = subSectionNode[i]["height"].as<float>();
        float x = subSectionNode[i]["xCoord"].as<float>();
        float y = subSectionNode[i]["yCoord"].as<float>();
        Area area(x, y, width, height);
        this->add_texture(id, area, subSectionName);
    }
}

void MapCreator::add_multiple_colors(std::string & subSectionName){
    YAML::Node subSectionNode = this->baseNode[subSectionName.c_str()];
    float width = subSectionNode["width"].as<float>();
    float height = subSectionNode["height"].as<float>();
    YAML::Node idCoordsNode = subSectionNode["id_coordinates"];
    for (int j = 0; j < (int)idCoordsNode.size(); ++j){
        uint32_t id = idCoordsNode[j]["id"].as<uint32_t>();  
        float x = idCoordsNode[j]["xCoord"].as<float>();
        float y = idCoordsNode[j]["yCoord"].as<float>();
        // Parece que al YAML no le gusta que lo interprete directamente como uint8_t
        uint8_t redMod = (uint8_t) idCoordsNode[j]["redMod"].as<uint32_t>();
        uint8_t greenMod = (uint8_t) idCoordsNode[j]["greenMod"].as<uint32_t>();
        uint8_t blueMod = (uint8_t) idCoordsNode[j]["blueMod"].as<uint32_t>();
        Area area(x, y, width, height);
        this->add_texture(id, area, redMod, greenMod, blueMod, subSectionName);
    }
}

void MapCreator::add_map(){
    YAML::Node sectionsNode = this->baseNode["sections"];
    for (int i = 0; i < (int)sectionsNode.size(); ++i){
        std::string subSectionName = sectionsNode[i].as<std::string>();
        if (subSectionName == "barriers"){
            this->add_multiple_sizes(subSectionName);
            continue;
        }
        if (subSectionName == "chells" || subSectionName == "pin_tools"){
            this->add_multiple_colors(subSectionName);
            continue;
        }
        YAML::Node subSectionNode = this->baseNode[subSectionName.c_str()];
        float width = subSectionNode["width"].as<float>();
        float height = subSectionNode["height"].as<float>();
        YAML::Node idCoordsNode = subSectionNode["id_coordinates"];
        for (int j = 0; j < (int)idCoordsNode.size(); ++j){
            uint32_t id = idCoordsNode[j]["id"].as<uint32_t>();  
            float x = idCoordsNode[j]["xCoord"].as<float>();
            float y = idCoordsNode[j]["yCoord"].as<float>();
            Area area(x, y, width, height);
            this->add_texture(id, area, subSectionName);
        }
    }
}