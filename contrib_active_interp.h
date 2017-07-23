//
// Created by Shae Bolt on 7/15/2017.
//

#ifndef GLPROJECT_CONTRIB_ACTIVE_INTERP_H
#define GLPROJECT_CONTRIB_ACTIVE_INTERP_H

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>
#include <random>
#include <numeric>
#include <limits>

double nonLinearActivationFunction(double value);

double linearActivationFunction(double value);

double cosineInterpolate(double a, double b, double t);

double linearInterpolate(double a, double b, double t);

template<class PrngHasher>
class GradientFixed4Contributor {
//    const std::array<glm::vec2, 4> vector_choice = {glm::vec2(1.0, 1.0), glm::vec2(-1.0, 1.0), glm::vec2(1.0, -1.0),
//                                                    glm::vec2(-1.0, -1.0)};
    const std::array<glm::vec2, 8> vector_choice = {glm::vec2(1.0, 1.0), glm::vec2(-1.0, 1.0), glm::vec2(1.0, -1.0),
                                                    glm::vec2(-1.0, -1.0), glm::vec2(sqrt(2), 0),
                                                    glm::vec2(-sqrt(2), 0), glm::vec2(0, sqrt(2)),
                                                    glm::vec2(0, -sqrt(2))};
    PrngHasher m_prng_hasher;
    std::uint64_t m_mod_val;
    std::uint64_t m_and_var;
public:
    GradientFixed4Contributor(std::uint64_t mod_var) {
        m_mod_val = mod_var;
    }

    double operator()(std::uint32_t x, std::uint32_t y, double dist_x, double dist_y, std::uint64_t offset = 0) {
        double temp = glm::dot(vector_choice[m_prng_hasher(x, y, offset)& 3], {dist_x, dist_y});

        return ((temp) * 128.0) + 128.0;
    }
};

template<class PrngHasher>
class ValueFixedValueContributor {
    PrngHasher m_prng_hasher;
    std::uint64_t m_mod_val;
    std::uint64_t m_and_var;
public:
    ValueFixedValueContributor(std::uint64_t mod_var) {
        m_mod_val = mod_var;
    }

    double operator()(std::uint32_t x, std::uint32_t y, double dist_x, double dist_y, std::uint64_t offset = 0) {
        return ((m_prng_hasher(x, y, offset) & 255));
    }
};


#endif //GLPROJECT_CONTRIB_ACTIVE_INTERP_H
