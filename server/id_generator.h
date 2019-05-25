//
// Created by franciscosicardi on 25/05/19.
//

#ifndef PORTAL_ID_GENERATOR_H
#define PORTAL_ID_GENERATOR_H


#include <stdint-gcc.h>

class IdGenerator {
private:
    static uint32_t lastId;
public:
    static uint32_t getNewId();
};


#endif //PORTAL_ID_GENERATOR_H
