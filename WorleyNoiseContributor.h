//
// Created by Shae Bolt on 8/3/2017.
//

#ifndef GLPROJECT_WORLEYNOISECONTRIBUTOR_H
#define GLPROJECT_WORLEYNOISECONTRIBUTOR_H

#include <array>

#include <cstdint>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

template<class PrngHasher>
class WorleyNoiseContributor {

    PrngHasher m_prng_hasher;
    std::uint64_t m_mod_val;
    std::uint64_t m_and_var;
public:
    WorleyNoiseContributor(std::uint64_t mod_var) {
        m_mod_val = mod_var;
    }

    glm::vec2 random2( glm::vec2 p ) {
        const glm::vec2 test = glm::vec2(glm::dot(p,glm::vec2(127.1,311.7)),glm::dot(p,glm::vec2(269.5,183.3)));
        return glm::fract(glm::sin(test)*43758.5453f);
    }

    double operator()(std::uint32_t inx, std::uint32_t iny, double dist_x, double dist_y, std::uint64_t offset = 0) {

        // Tile the space
        glm::vec2 i_st(inx, iny);
        glm::vec2 f_st(dist_x, dist_y);

        float m_dist = 1.0;  // minimun distance

        for (int y= -1; y <= 1; y++) {
            for (int x= -1; x <= 1; x++) {
                // Neighbor place in the grid
                glm::vec2 neighbor = glm::vec2(float(x),float(y));

                // Random position from current + neighbor place in the grid
                glm::vec2 point = random2(i_st + neighbor);

                // Animate the point
                point = 0.5f + 0.5f*sin(1.0f + 6.2831f*point);

                // Vector between the pixel and the point
                glm::vec2 diff = neighbor + point - f_st;

                // Distance to the point
                float dist = glm::length(diff);

                // Keep the closer distance
                m_dist = glm::min(m_dist, dist);
            }
        }

        // Draw the min distance (distance field)
        return ((m_dist) * 128.0) + 128.0;
    }
};


#endif //GLPROJECT_WORLEYNOISECONTRIBUTOR_H
