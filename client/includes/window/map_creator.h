#ifndef MAP_CREATOR_H
#define MAP_CREATOR_H

#include "window.h"
#include "yaml-cpp/yaml.h"

#include <cstdint>

class MapCreator {
private: 
    Window & window;
    YAML::Node & baseNode;
public:
    /*
    PRE: Recibe la configuracion del mapa (YAML::Node) 
    a crear, y la ventana (Window &) donde se agregaran 
    las texturas del mismo.
    POST: Inicializa un creador de mapa. 
    */
    MapCreator(YAML::Node & mapConfig, Window & window);

    /*Destruye el creador de mapa*/
    ~MapCreator();
    
    void add_texture(uint32_t id, Area area, std::string & subSectionName);

    void add_texture(
        uint32_t id, 
        Area area,
        uint8_t redMod,
        uint8_t greenMod,
        uint8_t blueMod,
        std::string & subSectionName
    );

    void add_multiple_sizes(std::string & subSectionName);

    void add_multiple_colors(std::string & subSectionName);

    void add_map();
};

#endif // MAP_CREATOR_H
