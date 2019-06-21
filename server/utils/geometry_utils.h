//
// Created by franciscosicardi on 20/06/19.
//

#ifndef PORTAL_GEOMETRY_UTILS_H
#define PORTAL_GEOMETRY_UTILS_H

#include <Box2D/Common/b2Math.h>

float32 angle_between_vectors(b2Vec2 v1, b2Vec2 v2);
b2Vec2 rotate_vector_counterclockwise(float32 angle, b2Vec2 vector);
b2Vec2 normal_reflection(b2Vec2 input, b2Vec2 normal);

#endif //PORTAL_GEOMETRY_UTILS_H
