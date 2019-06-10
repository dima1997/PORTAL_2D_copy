#include "../../includes/window/map_creator.h"

#include "../../includes/window/window.h"
#include "../../includes/window/texture_factory.h"
#include "../../includes/textures/common_texture/texture.h"

#include <configs_yaml/config_paths.h>
#include <cstdint>
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

void MapCreator::add_texture(uint32_t id, Area area, 
                            std::string & subSectionName){
    if (subSectionName == "blocks_metal"){
        this->add_block_metal(id, area);
        return;
    }
    if(subSectionName == "blocks_rock") {
        this->add_block_rock(id, area);
        return;
    }
    if (subSectionName == "blocks_acid") {
        this->add_block_acid(id, area);
        return;
    }
    if (subSectionName == "portals_blue") {
        this->add_portal_blue(id, area);
         return;
    }
    if (subSectionName == "portals_orange") {
        this->add_portal_orange(id, area);
        return;
    }
    if (subSectionName ==  "doors_one") {
        this->add_door_one(id, area);
        return;   
    }
    if (subSectionName == "buttons") {
        this->add_button(id, area);
        return;
    }
    if (subSectionName == "rocks_one") {
        this->add_rock_one(id, area);
        return;
    }
    if (subSectionName == "barriers") {
        this->add_barrier(id, area);
        return;
    }
    if (subSectionName == "energy_balls_green") {
        this->add_energy_ball_green(id, area);
        return;
    }
    if (subSectionName == "receivers") {
        this->add_receiver(id, area);
        return;   
    }
    if (subSectionName == "emitters_right") {
        this->add_emitter_right(id, area);
        return;
    }
    if (subSectionName == "triangles_botom_left") {
        this->add_triangle_botom_left(id, area);
        return;
    }
    if (subSectionName == "triangles_botom_right") {
        this->add_triangle_botom_right(id, area);
        return;
    }
    if (subSectionName == "triangles_top_left") {
        this->add_triangle_top_left(id, area);
        return;
    }
    if (subSectionName == "triangles_top_right") {
        this->add_triangle_top_right(id, area);
        return;            
    }
    if (subSectionName == "cakes") {
        this->add_cake(id, area);
        return;
    }
    if (subSectionName == "chells") {
        this->add_chell(id, area);
        return;
    }
    if (subSectionName == "background"){
        this->add_background(id, area);
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

void MapCreator::add_door_textures() {
    std::string subSectionName = "doors_one";
    YAML::Node subSectionNode = this->baseNode[subSectionName];
    float width = subSectionNode["width"].as<float>();
    float height = subSectionNode["height"].as<float>();
    YAML::Node idCoordsNode = subSectionNode["id_coordinates"];
    for (int j = 0; j < (int)idCoordsNode.size(); ++j){
        uint32_t id = idCoordsNode[j]["id"].as<uint32_t>();  
        float x = idCoordsNode[j]["xCoord"].as<float>();
        float y = idCoordsNode[j]["yCoord"].as<float>();
        YAML::Node conditionsNode = idCoordsNode[j]["conditions"];
        bool is_open = conditionsNode[0]["condition"].as<bool>(); 
        // Hardcode, seria mejor si el servidor me envia el estado en el que inicia
        Area area(x, y, width, height);
        this->add_texture(id, area, subSectionName);
        /*
        if (is_open){
            this->window.switch_texture(id);
        }
        */
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
        if (subSectionName == "doors_one"){
            this->add_door_textures();
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