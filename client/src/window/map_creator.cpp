#include "../../includes/window/map_creator.h"

#include "../../includes/window/window.h"
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
    std::pair<std::string, texture_creator>("records",TextureFactory::create_record)
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

/*
void MapCreator::add_block_metal(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_block_metal(area)));
}

void MapCreator::add_block_rock(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_block_rock(area)));
}

void MapCreator::add_block_acid(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_block_acid(area)));
}

void MapCreator::add_portal_blue(uint32_t id, Area area
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_portal_blue(area)));
}

void MapCreator::add_portal_orange(uint32_t id, Area area
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_portal_orange(area)));
}

void MapCreator::add_door_one(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_door_one(area)));
}

void MapCreator::add_button(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_button(area)));
}

void MapCreator::add_rock_one(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_rock_one(area)));
}

void MapCreator::add_rock_two(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_rock_two(area)));
}

void MapCreator::add_rock_three(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_rock_three(area)));
}

void MapCreator::add_rock_four(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_rock_four(area)));
}

void MapCreator::add_rock_five(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_rock_five(area)));
}

void MapCreator::add_rock_six(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_rock_six(area)));
}

void MapCreator::add_rock_seven(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_rock_seven(area)));
}

void MapCreator::add_rock_eight(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_rock_eight(area)));
}

void MapCreator::add_barrier(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_barrier(area)));
}

void MapCreator::add_energy_ball_green(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
){
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_energy_ball_green(
        area,
        uint8_t redMod, 
        uint8_t greenMod, 
        uint8_t blueMod
    )));
}

void MapCreator::add_receiver(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_receiver(
        area,
        uint8_t redMod, 
        uint8_t greenMod, 
        uint8_t blueMod
    )));
}

void MapCreator::add_emitter_right(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_emitter_right(
        area,
        uint8_t redMod, 
        uint8_t greenMod, 
        uint8_t blueMod
        )));
}

void MapCreator::add_emitter_up(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_emitter_up(
        area,
        uint8_t redMod, 
        uint8_t greenMod, 
        uint8_t blueMod
    )));
}

void MapCreator::add_emitter_left(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_emitter_left(
        area,
        uint8_t redMod, 
        uint8_t greenMod, 
        uint8_t blueMod
        )));
}

void MapCreator::add_emitter_down(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(tF.create_emitter_down(
            area,
            uint8_t redMod, 
            uint8_t greenMod, 
            uint8_t blueMod
    )));
}

void MapCreator::add_triangle_botom_left(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_triangle_botom_left(area,
            uint8_t redMod, 
            uint8_t greenMod, 
            uint8_t blueMod
        )
    ));
}

void MapCreator::add_triangle_botom_right(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_triangle_botom_right(area,
            uint8_t redMod, 
            uint8_t greenMod, 
            uint8_t blueMod
        )
    ));
}

void MapCreator::add_triangle_top_left(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_triangle_top_left(area,
            uint8_t redMod, 
            uint8_t greenMod, 
            uint8_t blueMod
        )
    ));
}

void MapCreator::add_triangle_top_right(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_triangle_top_right(
            area,
            uint8_t redMod, 
            uint8_t greenMod, 
            uint8_t blueMod
        )
    ));
}

void MapCreator::add_cake(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_cake(
            area,
            uint8_t redMod, 
            uint8_t greenMod, 
            uint8_t blueMod
        )
    ));
}

void MapCreator::add_chell(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_chell(
            area,
            uint8_t redMod, 
            uint8_t greenMod, 
            uint8_t blueMod
        )
    ));
}

void MapCreator::add_background(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_background(area,
            uint8_t redMod, 
            uint8_t greenMod, 
            uint8_t blueMod
        )
    ));
}

void MapCreator::add_record(
    uint32_t id, 
    Area area, 
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod
)
{
    TextureFactory tF(this->window);
    this->window.add_texture(id,std::move(
        tF.create_record(
            area,
            uint8_t redMod, 
            uint8_t greenMod, 
            uint8_t blueMod
        )
    ));
    this->window.set_record_id(id);
}

void MapCreator::add_specific_texture(
    uint32_t id, 
    Area area,
    uint8_t redMod, 
    uint8_t greenMod, 
    uint8_t blueMod,
    std::string & subSectionName
)
*/
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
        //Levanto error ...
        return;
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
    /*
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
    if (subSectionName == "rocks_two") {
        this->add_rock_two(id, area);
        return;
    }
    if (subSectionName == "rocks_three") {
        this->add_rock_three(id, area);
        return;
    }
    if (subSectionName == "rocks_four") {
        this->add_rock_four(id, area);
        return;
    }
    if (subSectionName == "rocks_five") {
        this->add_rock_five(id, area);
        return;
    }
    if (subSectionName == "rocks_six") {
        this->add_rock_six(id, area);
        return;
    }
    if (subSectionName == "rocks_seven") {
        this->add_rock_seven(id, area);
        return;
    }
    if (subSectionName == "rocks_eight") {
        this->add_rock_eight(id, area);
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
    if (subSectionName == "emitters_up"){
        this->add_emitter_up(id, area);
        return;
    }
    if (subSectionName == "emitters_left"){
        this->add_emitter_left(id, area);
        return;
    }
    if (subSectionName == "emitters_down"){
        this->add_emitter_down(id, area);
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
        return;
    }
    if (subSectionName == "records"){
        this->add_record(id, area);
        return;
    }
    */
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
        uint8_t redMod = idCoordsNode[j]["redMod"].as<uint8_t>();
        uint8_t greenMod = idCoordsNode[j]["greenMod"].as<uint8_t>();
        uint8_t blueMod = idCoordsNode[j]["blueMod"].as<uint8_t>();
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
        if (subSectionName == "chells"){
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