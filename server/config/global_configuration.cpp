//
// Created by franciscosicardi on 24/06/19.
//

#include <yaml-cpp/yaml.h>
#include "global_configuration.h"

#define CONFIG_FILE_PATH "server_config.yaml"

GlobalConfiguration::GlobalConfiguration():
    file(YAML::LoadFile(CONFIG_FILE_PATH)),
    defaultPort(file["server"]["default_port"].as<std::string>()),
    requestExecutorsNumber(file["server"]["request_executors"].as<int>()),
    waitBeforeStartSeconds(file["game_loop"]["wait_before_start_seconds"].as<int>()),
    stepMaxTimeMicroSeconds(file["game_loop"]["step_max_time_microseconds"].as<double>()),
    availableMaps(file["available_maps"].as<std::vector<std::string>>()),
    timeStepSeconds(file["simulation"]["time_step_seconds"].as<float>()),
    velocityIterations(file["simulation"]["velocity_iterations"].as<int>()),
    positionIterations(file["simulation"]["position_iterations"].as<int>()),
    gravityX(file["simulation"]["game_options"]["gravity_x"].as<float>()),
    gravityY(file["simulation"]["game_options"]["gravity_y"].as<float>()) {}

GlobalConfiguration::~GlobalConfiguration() = default;
