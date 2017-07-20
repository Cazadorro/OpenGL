//
// Created by Shae Bolt on 7/15/2017.
//

#include "OctaveNoise.h"

glm::vec3 Barycentric(const glm::vec2 p, const glm::vec2 a, const glm::vec2 b, const glm::vec2 c) {
    glm::vec2 v0 = b - a, v1 = c - a, v2 = p - a;
    float den = v0.x * v1.y - v1.x * v0.y;
    glm::vec3 barycentric;
    barycentric.x = (v2.x * v1.y - v1.x * v2.y) / den;
    barycentric.y = (v0.x * v2.y - v2.x * v0.y) / den;
    barycentric.z = 1.0f - barycentric.x - barycentric.y;
    return barycentric;
}
