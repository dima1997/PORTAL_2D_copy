//
// Created by franciscosicardi on 24/06/19.
//

#ifndef PORTAL_GLOBAL_CONFIGURATION_H
#define PORTAL_GLOBAL_CONFIGURATION_H


#include <yaml-cpp/node/node.h>

class GlobalConfiguration {
private:
    YAML::Node file;
public:
    GlobalConfiguration();
    ~GlobalConfiguration();
    const std::string defaultPort;
    const int requestExecutorsNumber;
    const int waitBeforeStartSeconds;
    const double stepMaxTimeMicroSeconds;
    const std::vector<std::string> availableMaps;
    const float timeStepSeconds;
    const int velocityIterations;
    const int positionIterations;
    const float gravityX;
    const float gravityY;
    const float chellMoveSpeed;
    const float chellJumpSpeed;
    const float chellJumpTimeoutMilliseconds;
    const float energy_ball_speed;
    const float energy_ball_reset_time_milliseconds;
    const float pin_tool_reset_time_milliseconds;
};

const GlobalConfiguration CONFIG;


#endif //PORTAL_GLOBAL_CONFIGURATION_H
