#ifndef CONFIG_PATH_H
#define CONFIG_PATH_H

#include <map>
#include <cstdint>
#include <string>

const std::map<uint8_t, std::string> CONFIG_PATHS({
    std::make_pair(0, "config_0.yaml"),
    std::make_pair(1, "config_1.yaml"),
    std::make_pair(2, "config_2.yaml"),

});

#endif // CONFIG_PATH_H
