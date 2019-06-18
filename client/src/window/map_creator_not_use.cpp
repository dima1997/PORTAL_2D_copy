#include "../../includes/window/map_creator.h"

#include "../../includes/window/window.h"
#include "../../includes/window/texture_factory.h"
#include "../../includes/window/os_exception.h"
#include "../../includes/textures/common_texture/texture.h"

#include <configs_yaml/config_paths.h>
#include <cstdint>

typedef void (&addTextureMethod_t)(uint32_t,Area);

const std::map<std::string, addTextureMethod_t> ADD_TEXTURE_METHODS({
    std::pair<std::string, addTextureMethod_t>(
        "blocks_metal", MapCreator::add_block_metal
    ),
    std::pair<std::string, addTextureMethod_t>(
        "blocks_rock", MapCreator::add_block_rock
    ),
    std::pair<std::string, addTextureMethod_t>(
        "blocks_acid", MapCreator::add_block_acid
    ),
    std::pair<std::string, addTextureMethod_t>(
        "portals_blue", MapCreator::add_portal_blue
    ),
    std::pair<std::string, addTextureMethod_t>(
        "portals_orange", MapCreator::add_portal_orange
    ),
    std::pair<std::string, addTextureMethod_t>(
        "doors_one", MapCreator::add_door_one
    ),
    std::pair<std::string, addTextureMethod_t>(
        "buttons", MapCreator::add_button
    ),
    std::pair<std::string, addTextureMethod_t>(
        "rocks_one", MapCreator::add_rock_one
    ),
    std::pair<std::string, addTextureMethod_t>(
        "barriers", MapCreator::add_barrier
    ),
    std::pair<std::string, addTextureMethod_t>(
        "energy_balls_green", MapCreator::add_energy_ball_green
    ),
    std::pair<std::string, addTextureMethod_t>(
        "receivers", MapCreator::add_receiver
    ),
    std::pair<std::string, addTextureMethod_t>(
        "emitters_right", MapCreator::add_emitter_right
    ),
    std::pair<std::string, addTextureMethod_t>(
        "emitters_up", MapCreator::emitters_up
    ),
    std::pair<std::string, addTextureMethod_t>(
        "emitters_left", MapCreator::emitters_left
    ),
    std::pair<std::string, addTextureMethod_t>(
        "emitters_down", MapCreator::add_emitter_down
    ),
    std::pair<std::string, addTextureMethod_t>(
        "triangles_botom_left", MapCreator::add_triangle_botom_left
    ),
    std::pair<std::string, addTextureMethod_t>(
        "triangles_botom_right", MapCreator::add_triangle_botom_right
    ),
    std::pair<std::string, addTextureMethod_t>(
        "triangles_top_left", MapCreator::add_triangle_top_left
    ),
    std::pair<std::string, addTextureMethod_t>(
        "triangles_top_right", MapCreator::add_triangle_top_right
    ),
    std::pair<std::string, addTextureMethod_t>(
        "cakes", MapCreator::add_cake
    ),
    std::pair<std::string, addTextureMethod_t>(
        "chells", MapCreator::add_chell
    ),
    std::pair<std::string, addTextureMethod_t>(
        "background", MapCreator::add_background
    ),
    std::pair<std::string, addTextureMethod_t>(
        "records", MapCreator::add_record
    )
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

void MapCreator::add_block_metal(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_block_metal(area)));
}

void MapCreator::add_block_rock(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_block_rock(area)));
}

void MapCreator::add_block_acid(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_block_acid(area)));
}

void MapCreator::add_portal_blue(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_portal_blue(area)));
}

void MapCreator::add_portal_orange(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_portal_orange(area)));
}

void MapCreator::add_door_one(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_door_one(area)));
}

void MapCreator::add_button(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_button(area)));
}

void MapCreator::add_rock_one(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_rock_one(area)));
}

void MapCreator::add_barrier(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_barrier(area)));
}

void MapCreator::add_energy_ball_green(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_energy_ball_green(area)));
}

void MapCreator::add_receiver(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_receiver(area)));
}

void MapCreator::add_emitter_right(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_emitter_right(area)));
}

void MapCreator::add_emitter_up(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_emitter_up(area)));
}

void MapCreator::add_emitter_left(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_emitter_left(area)));
}

void MapCreator::add_emitter_down(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_emitter_down(area)));
}

void MapCreator::add_triangle_botom_left(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_triangle_botom_left(area)
    ));
}

void MapCreator::add_triangle_botom_right(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_triangle_botom_right(area)
    ));
}

void MapCreator::add_triangle_top_left(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_triangle_top_left(area)
    ));
}

void MapCreator::add_triangle_top_right(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_triangle_top_right(area)
    ));
}

void MapCreator::add_cake(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_cake(area)
    ));
}

void MapCreator::add_chell(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_chell(area)
    ));
}

void MapCreator::add_background(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_background(area)
    ));
}

void MapCreator::add_record(uint32_t id, Area area){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_record(area)
    ));
    this->window.set_record_id(id);
}


void MapCreator::add_texture(uint32_t id, Area area, 
                            std::string & subSectionName){
    try{
        ADD_TEXTURE_METHODS.at(subSectionName)(id, area);
    } catch (std::out_of_range & error){
        std::stringstream err;
         err << "No sub-section with name : " << subSectionName << "\n";
        throw OSException(err.str().c_str(), "");
    }
}

void MapCreator::add_custom_textures(std::string & subSectionName){
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

void MapCreator::add_map(){
    TextureFactory tF(this->window);
    YAML::Node sectionsNode = this->baseNode["sections"];
    for (int i = 0; i < (int)sectionsNode.size(); ++i){
        std::string subSectionName = sectionsNode[i].as<std::string>();
        if (subSectionName == "barriers"){
            this->add_custom_textures(subSectionName);
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