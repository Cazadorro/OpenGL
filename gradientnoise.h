//
// Created by Shae Bolt on 7/14/2017.
//

#ifndef GLPROJECT_GRADIENTNOISE_H
#define GLPROJECT_GRADIENTNOISE_H

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>
#include <random>

class GradientNoise {
    //todo, might want to change this?
    std::mt19937_64 rng;
    std::uint64_t m_seed;
    std::uniform_int_distribution<std::uint8_t> distribution;
    // corner points or what have you that we test the contribution of.
    const std::array<glm::vec2, 4> vector_choice = {glm::vec2(1.0, 1.0), glm::vec2(-1.0, 1.0), glm::vec2(1.0, -1.0),
                                                    glm::vec2(-1.0, -1.0)};
    const std::array<glm::vec3, 12> fixed_points = {
            glm::vec3(1.0, 1.0, 0.0), glm::vec3(-1.0, 1.0, 0.0), glm::vec3(1.0, -1.0, 0.0), glm::vec3(-1.0, -1.0, 0.0),
            glm::vec3(1.0, 0.0, 1.0), glm::vec3(-1.0, 0.0, 1.0), glm::vec3(1.0, 0.0, -1.0), glm::vec3(-1.0, 0.0, -1.0),
            glm::vec3(0.0, 1.0, 1.0), glm::vec3(0.0, -1.0, 1.0), glm::vec3(0.0, 1.0, -1.0), glm::vec3(0.0, -1.0, -1.0)
    };

public:
    GradientNoise(uint64_t seed) {
        m_seed = seed;
        //rng.seed(m_seed);
        distribution = std::uniform_int_distribution<std::uint8_t>(0, 3);
    }

    // 0 -> 1
    double nonLinearActivationFunction(double value) {
        return value * value * value * (value * (value * 6.0 - 15.0) + 10.0);
    }

    // 0 -> 1
    //replace activation with cosine interpolation?
    double interpolate(double a, double b, double t) {
        return (1 - t) * a + t * b;
    }

    double noise(double x, double y) {
        //first get the bottom left corner associated
        // with these coordinates
        int corner_x = std::floor(x);
        int corner_y = std::floor(y);

        // then get the respective distance from that corner
        double dist_x = x - corner_x;
        double dist_y = y - corner_y;

        double corner_0_contrib; // bottom left
        double corner_1_contrib; // top left
        double corner_2_contrib; // top right
        double corner_3_contrib; // bottom right

        rng.seed((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y) + m_seed);
        // each xy pair turns into distance vector from respective corner, corner zero is our starting corner (bottom
        // left)
        corner_0_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x, dist_y});
        rng.seed((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y + 1) + m_seed);
        corner_1_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x, dist_y - 1});
        rng.seed((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y + 1) + m_seed);
        corner_2_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x - 1, dist_y - 1});
        rng.seed((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y) + m_seed);
        corner_3_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x - 1, dist_y});

        double u = nonLinearActivationFunction(dist_x);
        double v = nonLinearActivationFunction(dist_y);
        //double w = nonLinearActivationFunction(z);

        double x_bottom = interpolate(corner_0_contrib, corner_3_contrib, u);
        double x_top = interpolate(corner_1_contrib, corner_2_contrib, u);
        double total_xy = interpolate(x_bottom, x_top, v);
        return total_xy;





//        double corner_11_contrib = glm::dot(glm::vec2(1.0, 1.0), {x, y});
//        double corner_n11_contrib = glm::dot(glm::vec2(-1.0, 1.0), {x, y});
//        double corner_1n1_contrib = glm::dot(glm::vec2(1.0, -1.0), {x, y});
//        double corner_n1n1_contrib = glm::dot(glm::vec2(-1.0, -1.0), {x, y});


    }
};


#endif //GLPROJECT_GRADIENTNOISE_H
