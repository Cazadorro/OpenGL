//
// Created by Shae Bolt on 7/22/2017.
//

#ifndef GLPROJECT_GRADIENTFIXED_H
#define GLPROJECT_GRADIENTFIXED_H

#include <array>

#include <cstdint>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GradientFixed {

};

constexpr float sqrt2 = sqrt(2);

template<class PrngHasher>
class GradientFixed4Contributor {
//    const std::array<glm::vec2, 4> vector_choice = {glm::vec2(1.0, 1.0), glm::vec2(-1.0, 1.0), glm::vec2(1.0, -1.0),
//                                                    glm::vec2(-1.0, -1.0)};
    const std::array<glm::vec2, 16> vector_choice = {glm::vec2(1.0, 1.0),
                                                     glm::vec2(-1.0, 1.0),
                                                     glm::vec2(1.0, -1.0),
                                                     glm::vec2(-1.0, -1.0),
                                                     glm::vec2(sqrt(2), 0),
                                                     glm::vec2(-sqrt(2), 0),
                                                     glm::vec2(0, sqrt(2)),
                                                     glm::vec2(0, -sqrt(2)),
                                                     glm::vec2(-sqrt(3) / 2, 1 / 2) * sqrt2,
                                                     glm::vec2(-1 / 2, sqrt(3) / 2) * sqrt2,
                                                     glm::vec2(sqrt(3) / 2, -1 / 2) * sqrt2,
                                                     glm::vec2(1 / 2, -sqrt(3) / 2) * sqrt2,
                                                     glm::vec2(sqrt(3) / 2, 1 / 2) * sqrt2,
                                                     glm::vec2(1 / 2, sqrt(3) / 2) * sqrt2,
                                                     glm::vec2(-sqrt(3) / 2, -1 / 2) * sqrt2,
                                                     glm::vec2(-1 / 2, -sqrt(3) / 2) * sqrt2};
    PrngHasher m_prng_hasher;
    std::uint64_t m_mod_val;
    std::uint64_t m_and_var;
public:
    GradientFixed4Contributor(std::uint64_t mod_var) {
        m_mod_val = mod_var;
    }

    double operator()(std::uint32_t x, std::uint32_t y, double dist_x, double dist_y, std::uint64_t offset = 0) {
        double temp = glm::dot(vector_choice[m_prng_hasher.hash32bit2D(x, y, offset) & 15], {dist_x, dist_y});

        return ((temp) * 128.0) + 128.0;
    }
};

template<class PrngHasher>
class GradientGenContributor {

    PrngHasher m_prng_hasher;
    std::uint64_t m_mod_val;
    std::uint64_t m_and_var;
public:
    GradientGenContributor(std::uint64_t mod_var) {
        m_mod_val = mod_var;
    }

    double operator()(std::uint32_t x, std::uint32_t y, double dist_x, double dist_y, std::uint64_t offset = 0) {
        static int temps = 1;
        std::uint64_t hash = m_prng_hasher.hash32bit2D(x, y, offset);
        hash ^= hash >> 32;

        double value_V = (m_prng_hasher.hash32bit2D(x, y, offset)&255)/128.0;
        //double value_y = m_prng_hasher.hash32bit2D(x, y, offset)/128.0;
        double value_x =(m_prng_hasher.hash32bit2D(x, y, offset)&255)/128.0;

        std::uint64_t value_h = m_prng_hasher.hash32bit2D(x, y, offset);
        value_x -= 1.0;
        double value_y = sqrt(1 - (value_x*value_x));
        value_h >>= 8;
        value_h &= 1;

        double cost = cosf(value_V*M_PI);
        double sint = sinf(value_V*M_PI);
        glm::vec2 generated1(cost,sint);
        double sintt = pow(-1, value_h) * sqrt(1 - (cost*cost));
        glm::vec2 generated(cost, sintt);
        double temp = glm::dot(generated * sqrtf(2), {dist_x, dist_y});

        return ((temp) * 128.0) + 128.0;
    }
};

#endif //GLPROJECT_GRADIENTFIXED_H
