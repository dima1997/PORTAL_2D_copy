//
// Created by franciscosicardi on 25/05/19.
//

#include "id_generator.h"

uint32_t IdGenerator::lastId = 0;

uint32_t IdGenerator::getNewId() {
    return lastId++;
}
