//
// Created by franciscosicardi on 19/05/19.
//

#ifndef PORTAL_WORLD_H
#define PORTAL_WORLD_H


#include <list>
#include <vector>
#include <Box2D/Dynamics/b2World.h>
#include "body_info.h"

class World {
private:
    b2Vec2 gravity;
    b2World *world;
    std::vector<BodyInfo*> bodies;
    void loadMap(uint8_t mapId);
public:
    explicit World(uint8_t map_id);
    World(World &&other) noexcept;
    World &operator=(World &&other) noexcept;
    ~World();
    void step(std::list<BodyInfo *> &updated);
    void createRockBlock(float32 x_pos, float32 y_pos);
    void createChell(float32 x_pos, float32 y_pos, uint8_t playerId);
};


#endif //PORTAL_WORLD_H
