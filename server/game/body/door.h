//
// Created by franciscosicardi on 09/06/19.
//

#ifndef PORTAL_DOOR_H
#define PORTAL_DOOR_H


#include <unordered_map>
#include <vector>
#include "body.h"

class Door: public Body {
private:
    void createBody(float32 xPos, float32 yPos) override;
    std::vector<std::unordered_map<uint32_t, bool>> conditions;
    std::vector<std::unordered_map<uint32_t, bool>> current;
    bool lastStatus;
    bool isOpen();
public:
    Door(b2World &world, float32 xPos, float32 yPos, uint32_t id, std::vector<std::unordered_map<uint32_t, bool>> &conditions);
    Door(const Door &other);
    ~Door() override;
    body_type_t getBodyType() override;
    bool update();
    void updateConditionStatus(uint32_t id);
};


#endif //PORTAL_DOOR_H
