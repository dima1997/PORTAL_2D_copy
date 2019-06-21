//
// Created by franciscosicardi on 20/06/19.
//

#include "geometry_utils.h"
#include <stdlib.h>

float32 angle_between_vectors(b2Vec2 v1, b2Vec2 v2) {
    return acosf(b2Dot(v1, v2)/(v1.Length() * v2.Length()));
}

b2Vec2 rotate_vector_counterclockwise(float32 angle, b2Vec2 vector) {
    float32 cs = cosf(angle);
    float32 sn = sinf(angle);

    float32 newX = vector.x * cs - vector.y * sn;
    float32 newY = vector.x * sn + vector.y * cs;

    return b2Vec2(newX, newY);
}

b2Vec2 normal_reflection(b2Vec2 input, b2Vec2 normal) {
    float32 angle = angle_between_vectors(input, normal);
    b2Vec2 rot = rotate_vector_counterclockwise(angle, normal);
    if (abs(rot.x - input.x) <= b2_epsilon && abs(rot.y - input.y) <= b2_epsilon) {
        rot = rotate_vector_counterclockwise(-angle, normal);
    }
    return rot;
}