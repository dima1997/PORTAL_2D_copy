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
    gravityX(file["game_options"]["gravity_x"].as<float>()),
    gravityY(file["game_options"]["gravity_y"].as<float>()),
    chellMoveSpeed(file["game_options"]["chell"]["move_speed"].as<float>()),
    chellJumpSpeed(file["game_options"]["chell"]["jump_speed"].as<float>()),
    chellJumpTimeoutMilliseconds(file["game_options"]["chell"]["jump_timeout_milliseconds"].as<float>()),
    energy_ball_speed(file["game_options"]["energy_ball"]["speed"].as<float>()),
    energy_ball_reset_time_milliseconds(file["game_options"]["energy_ball"]["reset_time_milliseconds"].as<float>()),
    pin_tool_reset_time_milliseconds(file["game_options"]["pin_tool"]["reset_time_milliseconds"].as<float>())
    {}

GlobalConfiguration::~GlobalConfiguration() = default;
