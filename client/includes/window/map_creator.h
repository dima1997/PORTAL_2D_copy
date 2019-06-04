#ifndef MAP_CREATOR_H
#define MAP_CREATOR_H

#include "window.h"
#include "yaml-cpp/yaml.h"

#include <cstdint>

class MapCreator {
private: 
    Window & window;
    YAML::Node baseNode;
public:
    /*
    PRE: Recibe el id (unt8_t) del mapa a crear, 
    y la ventana (Window &) donde se agregaran 
    las texturas del mapa.
    POST: Inicializa un creador de mapa. 
    */
    MapCreator(uint8_t idMap, Window & window);

    /*Destruye el creador de mapa*/
    ~MapCreator();

    void add_block_metal(uint32_t id, Area area);

    void add_block_rock(uint32_t id, Area area);

    void add_block_acid(uint32_t id, Area area);

    void add_portal_blue(uint32_t id, Area area);

    void add_portal_orange(uint32_t id, Area area);

    void add_door_one(uint32_t id, Area area);

    void add_button(uint32_t id, Area area);

    void add_rock_one(uint32_t id, Area area);

    void add_barrier(uint32_t id, Area area);

    void add_energy_ball_green(uint32_t id, Area area);

    void add_receiver(uint32_t id, Area area);

    void add_emitter_right(uint32_t id, Area area);

    void add_triangle_botom_left(uint32_t id, Area area);

    void add_triangle_botom_right(uint32_t id, Area area);

    void add_triangle_top_left(uint32_t id, Area area);

    void add_triangle_top_right(uint32_t id, Area area);

    void add_cake(uint32_t id, Area area);

    void add_chell(uint32_t id, Area area);

    void add_background(uint32_t id, Area area);

    void add_texture(uint32_t id, Area area, std::string & subSectionName);

    void add_custom_textures(std::string & subSectionName);

    void add_map();
};

#endif // MAP_CREATOR_H