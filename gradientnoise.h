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
#include <numeric>
#include <limits>

class Xorshift128plus{
    uint64_t xorseed[2];
public:
    void seed(std::uint64_t a, std::uint64_t b){
        xorseed[0] = a;
        xorseed[1] = b;
    }

    uint64_t operator()(void) {
        uint64_t x = xorseed[0];
        const uint64_t y = xorseed[1];
        xorseed[0] = y;
        x ^= x << 23; // a
        xorseed[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
        return xorseed[1] + y;
    }
};



//class GradientNoise {
//    //todo, might want to change this?
//    std::mt19937_64 rng;
////    std::linear_congruential_engine<std::uint64_t, 123456788957ULL, 65432109857ULL,
////            std::numeric_limits<std::uint64_t>::max()> rng;
//    std::uint64_t m_seed;
//    std::uniform_int_distribution<std::uint8_t> distribution;
//    // corner points or what have you that we test the contribution of.
//    const std::array<glm::vec2, 4> vector_choice = {glm::vec2(1.0, 1.0), glm::vec2(-1.0, 1.0), glm::vec2(1.0, -1.0),
//                                                    glm::vec2(-1.0, -1.0)};
//    const std::array<glm::vec3, 12> fixed_points = {
//            glm::vec3(1.0, 1.0, 0.0), glm::vec3(-1.0, 1.0, 0.0), glm::vec3(1.0, -1.0, 0.0), glm::vec3(-1.0, -1.0, 0.0),
//            glm::vec3(1.0, 0.0, 1.0), glm::vec3(-1.0, 0.0, 1.0), glm::vec3(1.0, 0.0, -1.0), glm::vec3(-1.0, 0.0, -1.0),
//            glm::vec3(0.0, 1.0, 1.0), glm::vec3(0.0, -1.0, 1.0), glm::vec3(0.0, 1.0, -1.0), glm::vec3(0.0, -1.0, -1.0)
//    };
//
//public:
//    uint64_t xorseed[2];
//
//    double lce(std::uint64_t x, std::uint64_t a, std::uint64_t c, std::uint64_t m) {
//        return (a * x + c) % m;
//    }
//
//    void seedxorshift(std::uint64_t a, std::uint64_t b) {
//        xorseed[0] = a;
//        xorseed[1] = b;
//    }
//
//    uint64_t xorshift128plus(void) {
//        uint64_t x = xorseed[0];
//        const uint64_t y = xorseed[1];
//        xorseed[0] = y;
//        x ^= x << 23; // a
//        xorseed[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
//        return xorseed[1] + y;
//    }
//
//    GradientNoise(uint64_t seed) {
//        m_seed = seed;
//        //rng.seed(m_seed);
//        distribution = std::uniform_int_distribution<std::uint8_t>(0, 3);
//    }
//
//    // 0 -> 1
//    double nonLinearActivationFunction(double value) {
//        //return value * value * value * (value * (value * 6.0 - 15.0) + 10.0);
//        return value;
//    }
//
//    // 0 -> 1
//    //replace activation with cosine interpolation?
//    double interpolate(double a, double b, double t) {
//        //return (1 - t) * a + t * b;
//        double mu2 = (1 - cos(t * M_PI)) / 2;
//        return (a * (1 - mu2) + b * mu2);
//    }
//
//    double noise(double x, double y) {
//        //first get the bottom left corner associated
//        // with these coordinates
//        int corner_x = std::floor(x);
//        int corner_y = std::floor(y);
//
//        // then get the respective distance from that corner
//        double dist_x = x - corner_x;
//        double dist_y = y - corner_y;
//
//        double corner_0_contrib; // bottom left
//        double corner_1_contrib; // top left
//        double corner_2_contrib; // top right
//        double corner_3_contrib; // bottom right
//        //seedxorshift(corner_x, corner_y + m_seed);
////        std::uint64_t s1 = std::uint64_t(corner_x) *1024 + std::uint64_t(corner_y) + m_seed;
////        std::uint64_t s2 = std::uint64_t(corner_x) *1024 + std::uint64_t(corner_y+1) + m_seed;
////        std::uint64_t s3 = std::uint64_t(corner_x+1) *1024 + std::uint64_t(corner_y+1) + m_seed;
////        std::uint64_t s4 = std::uint64_t(corner_x+1)  *1024 + std::uint64_t(corner_y) + m_seed;
////
////        double s1 = lce(123456788957, corner_x, corner_y, 4);
////        double s2 = lce(123456788957, corner_x, corner_y + 1, 4);
////        double s3 = lce(123456788957, corner_x + 1, corner_y + 1, 4);
////        double s4 = lce(123456788957, corner_x + 1, corner_y, 4);
//
//        std::uint64_t s1 = ((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y) + m_seed);
//        std::uint64_t s2 = ((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y + 1) + m_seed);
//        std::uint64_t s3 = ((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y + 1) + m_seed);
//        std::uint64_t s4 = ((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y) + m_seed);
//
////        std::uint64_t s1 = ((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y) + m_seed) ^ 123456788957;
////        std::uint64_t s2 = ((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y + 1) + m_seed) ^ 123456788957;
////        std::uint64_t s3 = ((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y + 1) + m_seed) ^ 123456788957;
////        std::uint64_t s4 = ((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y) + m_seed) ^ 123456788957;
//
//
//
//        // each xy pair turns into distance vector from respective corner, corner zero is our starting corner (bottom
//        // left)
//        rng.seed(s1);
//        corner_0_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x, dist_y});
//        //seedxorshift(corner_x, corner_y + m_seed);
//        //seedxorshift(0, s1);
//        //corner_0_contrib = glm::dot(vector_choice[xorshift128plus() % 4], {dist_x, dist_y});
//        //xorshift128plus();
//        //corner_0_contrib = glm::dot(vector_choice[s1], {dist_x, dist_y});
//        //seedxorshift(corner_x, corner_y + 1 + m_seed);
//        //seedxorshift(0, s2);
//
//        rng.seed(s2);
//        corner_1_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x, dist_y - 1});
//        //corner_1_contrib = glm::dot(vector_choice[xorshift128plus() % 4], {dist_x, dist_y - 1});
//        //xorshift128plus();
//        //corner_1_contrib = glm::dot(vector_choice[s2], {dist_x, dist_y - 1});
//
//        rng.seed(s3);
//        corner_2_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x - 1, dist_y - 1});
//        //seedxorshift(corner_x + 1, corner_y + 1 + m_seed);
//        //seedxorshift(0, s3);
//        //corner_2_contrib = glm::dot(vector_choice[xorshift128plus() % 4], {dist_x - 1, dist_y - 1});
//        //xorshift128plus();
//        //corner_2_contrib = glm::dot(vector_choice[s3], {dist_x - 1, dist_y - 1});
//
//        rng.seed(s4);
//        corner_3_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x - 1, dist_y});
//        //seedxorshift(corner_x + 1, corner_y + m_seed);
//        //seedxorshift(0, s4);
//        //corner_3_contrib = glm::dot(vector_choice[xorshift128plus() %4], {dist_x - 1, dist_y});
//        //xorshift128plus();
//        //corner_3_contrib = glm::dot(vector_choice[s4], {dist_x - 1, dist_y});
//
//        double u = nonLinearActivationFunction(dist_x);
//        double v = nonLinearActivationFunction(dist_y);
//        //double w = nonLinearActivationFunction(z);
//
//        double x_bottom = interpolate(corner_0_contrib, corner_3_contrib, u);
//        double x_top = interpolate(corner_1_contrib, corner_2_contrib, u);
//        double total_xy = interpolate(x_bottom, x_top, v);
//        return total_xy;
//
//
//
//
//
////        double corner_11_contrib = glm::dot(glm::vec2(1.0, 1.0), {x, y});
////        double corner_n11_contrib = glm::dot(glm::vec2(-1.0, 1.0), {x, y});
////        double corner_1n1_contrib = glm::dot(glm::vec2(1.0, -1.0), {x, y});
////        double corner_n1n1_contrib = glm::dot(glm::vec2(-1.0, -1.0), {x, y});
//
//
//    }
//};

//constexpr std::uint64_t max_val = std::numeric_limits<std::uint64_t>::max();
//class GradientNoise {
//    std::linear_congruential_engine<std::uint64_t, 123456788957ULL, 65432109857ULL,
//            std::numeric_limits<std::uint64_t>::max()> rng;
//    std::uint64_t m_seed;
//    std::uniform_int_distribution<std::uint8_t> distribution;
//    const std::array<glm::vec2, 4> vector_choice = {glm::vec2(1.0, 1.0), glm::vec2(-1.0, 1.0), glm::vec2(1.0, -1.0),
//                                                    glm::vec2(-1.0, -1.0)};
//
//public:
//    GradientNoise(uint64_t seed) {
//        m_seed = seed;
//        //rng.seed(m_seed);
//        distribution = std::uniform_int_distribution<std::uint8_t>(0, 3);
//    }
//
//    // 0 -> 1
//    double nonLinearActivationFunction(double value) {
//        //return value * value * value * (value * (value * 6.0 - 15.0) + 10.0);
//        return value;
//    }
//
//    // 0 -> 1
//    //replace activation with cosine interpolation?
//    double interpolate(double a, double b, double t) {
//        //return (1 - t) * a + t * b;
//        double mu2 = (1 - cos(t * M_PI)) / 2;
//        return (a * (1 - mu2) + b * mu2);
//    }
//
//    double noise(double x, double y) {
//        //first get the bottom left corner associated
//        // with these coordinates
//        int corner_x = std::floor(x);
//        int corner_y = std::floor(y);
//
//        // then get the respective distance from that corner
//        double dist_x = x - corner_x;
//        double dist_y = y - corner_y;
//
//        double corner_0_contrib; // bottom left
//        double corner_1_contrib; // top left
//        double corner_2_contrib; // top right
//        double corner_3_contrib; // bottom right
//
//        std::uint64_t s1 = ((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y) + m_seed);
//        std::uint64_t s2 = ((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y + 1) + m_seed);
//        std::uint64_t s3 = ((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y + 1) + m_seed);
//        std::uint64_t s4 = ((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y) + m_seed);
//
//
//        // each xy pair turns into distance vector from respective corner, corner zero is our starting corner (bottom
//        // left)
//        rng.seed(s1);
//        corner_0_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x, dist_y});
//
//        rng.seed(s2);
//        corner_1_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x, dist_y - 1});
//
//
//        rng.seed(s3);
//        corner_2_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x - 1, dist_y - 1});
//
//
//        rng.seed(s4);
//        corner_3_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x - 1, dist_y});
//
//
//        double u = nonLinearActivationFunction(dist_x);
//        double v = nonLinearActivationFunction(dist_y);
//
//
//        double x_bottom = interpolate(corner_0_contrib, corner_3_contrib, u);
//        double x_top = interpolate(corner_1_contrib, corner_2_contrib, u);
//        double total_xy = interpolate(x_bottom, x_top, v);
//        return total_xy;
//    }
//};



//class GradientNoise {
//    std::mt19937_64 rng;
//    std::uint64_t m_seed;
//    std::uniform_int_distribution<std::uint8_t> distribution;
//    const std::array<glm::vec2, 4> vector_choice = {glm::vec2(1.0, 1.0), glm::vec2(-1.0, 1.0), glm::vec2(1.0, -1.0),
//                                                    glm::vec2(-1.0, -1.0)};
//
//public:
//    GradientNoise(uint64_t seed) {
//        m_seed = seed;
//        //rng.seed(m_seed);
//        distribution = std::uniform_int_distribution<std::uint8_t>(0, 3);
//    }
//
//    // 0 -> 1
//    double nonLinearActivationFunction(double value) {
//        //return value * value * value * (value * (value * 6.0 - 15.0) + 10.0);
//        return value;
//    }
//
//    // 0 -> 1
//    //replace activation with cosine interpolation?
//    double interpolate(double a, double b, double t) {
//        //return (1 - t) * a + t * b;
//        double mu2 = (1 - cos(t * M_PI)) / 2;
//        return (a * (1 - mu2) + b * mu2);
//    }
//
//    double noise(double x, double y) {
//        //first get the bottom left corner associated
//        // with these coordinates
//        int corner_x = std::floor(x);
//        int corner_y = std::floor(y);
//
//        // then get the respective distance from that corner
//        double dist_x = x - corner_x;
//        double dist_y = y - corner_y;
//
//        double corner_0_contrib; // bottom left
//        double corner_1_contrib; // top left
//        double corner_2_contrib; // top right
//        double corner_3_contrib; // bottom right
//
//        std::uint64_t s1 = ((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y) + m_seed);
//        std::uint64_t s2 = ((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y + 1) + m_seed);
//        std::uint64_t s3 = ((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y + 1) + m_seed);
//        std::uint64_t s4 = ((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y) + m_seed);
//
//
//        // each xy pair turns into distance vector from respective corner, corner zero is our starting corner (bottom
//        // left)
//        rng.seed(s1);
//        corner_0_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x, dist_y});
//
//        rng.seed(s2);
//        corner_1_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x, dist_y - 1});
//
//
//        rng.seed(s3);
//        corner_2_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x - 1, dist_y - 1});
//
//
//        rng.seed(s4);
//        corner_3_contrib = glm::dot(vector_choice[distribution(rng)], {dist_x - 1, dist_y});
//
//
//        double u = nonLinearActivationFunction(dist_x);
//        double v = nonLinearActivationFunction(dist_y);
//
//
//        double x_bottom = interpolate(corner_0_contrib, corner_3_contrib, u);
//        double x_top = interpolate(corner_1_contrib, corner_2_contrib, u);
//        double total_xy = interpolate(x_bottom, x_top, v);
//        return total_xy;
//    }
//};

class GradientNoise {
    std::mt19937_64 rng;
    std::uint64_t m_seed;
    std::uniform_int_distribution<std::uint8_t> distribution;
    const std::array<glm::vec2, 4> vector_choice = {glm::vec2(1.0, 1.0), glm::vec2(-1.0, 1.0), glm::vec2(1.0, -1.0),
                                                    glm::vec2(-1.0, -1.0)};

public:
    GradientNoise(uint64_t seed) {
        m_seed = seed;
        //rng.seed(m_seed);
        distribution = std::uniform_int_distribution<std::uint8_t>(0, 3);
    }

    // 0 -> 1
    double nonLinearActivationFunction(double value) {
        //return value * value * value * (value * (value * 6.0 - 15.0) + 10.0);
        return value;
    }

    // 0 -> 1
    //replace activation with cosine interpolation?
    double interpolate(double a, double b, double t) {
        //return (1 - t) * a + t * b;
        double mu2 = (1 - cos(t * M_PI)) / 2;
        return (a * (1 - mu2) + b * mu2);
    }

    double noise(double x, double y) {
        Xorshift128plus xorshifter;

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

        int itr = 0;

        std::uint64_t s1 = ((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y) + m_seed);
        std::uint64_t s2 = ((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y + 1) + m_seed);
        std::uint64_t s3 = ((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y + 1) + m_seed);
        std::uint64_t s4 = ((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y) + m_seed);

        // each xy pair turns into distance vector from respective corner, corner zero is our starting corner (bottom
        // left)
        std::uint64_t a;
        std::uint64_t b;
        xorshifter.seed(123456788957ULL, s1);
        a = xorshifter();
        b = xorshifter();
        xorshifter.seed(a,b);
        for(int i = 0; i < itr; i++){
            xorshifter();
        }
        corner_0_contrib = glm::dot(vector_choice[(xorshifter() % 257) & 3], {dist_x, dist_y});

        xorshifter.seed(123456788957ULL, s2);
        a = xorshifter();
        b = xorshifter();
        xorshifter.seed(a,b);
        for(int i = 0; i < itr; i++){
            xorshifter();
        }
        corner_1_contrib = glm::dot(vector_choice[(xorshifter() % 257) & 3], {dist_x, dist_y - 1});

        xorshifter.seed(123456788957ULL, s3);
        a = xorshifter();
        b = xorshifter();
        xorshifter.seed(a,b);
        for(int i = 0; i < itr; i++){
            xorshifter();
        }
        corner_2_contrib = glm::dot(vector_choice[(xorshifter() % 257) & 3], {dist_x - 1, dist_y - 1});

        xorshifter.seed(123456788957ULL, s4);
        a = xorshifter();
        b = xorshifter();
        xorshifter.seed(a,b);
        for(int i = 0; i < itr; i++){
            xorshifter();
        }

        corner_3_contrib = glm::dot(vector_choice[(xorshifter() % 257) & 3], {dist_x - 1, dist_y});

        double u = nonLinearActivationFunction(dist_x);
        double v = nonLinearActivationFunction(dist_y);

        double x_bottom = interpolate(corner_0_contrib, corner_3_contrib, u);
        double x_top = interpolate(corner_1_contrib, corner_2_contrib, u);
        double total_xy = interpolate(x_bottom, x_top, v);
        return total_xy;
    }
};


//class GradientNoise {
//    std::mt19937_64 rng;
//    std::uint64_t m_seed;
//    std::uniform_int_distribution<std::uint8_t> distribution;
//    const std::array<glm::vec2, 4> vector_choice = {glm::vec2(1.0, 1.0), glm::vec2(-1.0, 1.0), glm::vec2(1.0, -1.0),
//                                                    glm::vec2(-1.0, -1.0)};
//
//    const std::array<std::uint8_t, 8> bit_patterns = {0x15, 0x38, 0x32, 0x2C, 0x0D, 0x13, 0x07, 0x2A};
//public:
//    GradientNoise(uint64_t seed) {
//        m_seed = seed;
//        //rng.seed(m_seed);
//        distribution = std::uniform_int_distribution<std::uint8_t>(0, 3);
//    }
//
//    // 0 -> 1
//    double nonLinearActivationFunction(double value) {
//        //return value * value * value * (value * (value * 6.0 - 15.0) + 10.0);
//        return value;
//    }
//
//    // 0 -> 1
//    //replace activation with cosine interpolation?
//    double interpolate(double a, double b, double t) {
//        //return (1 - t) * a + t * b;
//        double mu2 = (1 - cos(t * M_PI)) / 2;
//        return (a * (1 - mu2) + b * mu2);
//    }
//
//    /// Given a coordinate (i, j) selects the B'th bit
//    std::uint8_t b(int i, int j, int B) const {
//        auto bit_index = 2*(i & (0b1 << B)) + (j & (0b1 << B));
//        return bit_patterns[bit_index];
//    }
//
//    /// Given a coordinate (i, j) generates a gradient vector
//    glm::vec2 grad(int i, int j) const {
//        int bit_sum = b(i,j,0) + b(j,i,1) + b(i,j,2) + b(j,i,3);
//        auto u = (bit_sum & 0b01) ? 1.0f : 0.0f;
//        auto v = (bit_sum & 0b10) ? 1.0f : 0.0f;
//        u = (bit_sum & 0b1000) ? -u : u;
//        v = (bit_sum & 0b0100) ? -v : v;
//        return {u, v};
//    }
//
//    double noise(double x, double y) {
//        //first get the bottom left corner associated
//        // with these coordinates
//        int corner_x = std::floor(x);
//        int corner_y = std::floor(y);
//
//        // then get the respective distance from that corner
//        double dist_x = x - corner_x;
//        double dist_y = y - corner_y;
//
//        double corner_0_contrib; // bottom left
//        double corner_1_contrib; // top left
//        double corner_2_contrib; // top right
//        double corner_3_contrib; // bottom right
//
////        std::uint64_t s1 = ((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y) + m_seed);
////        std::uint64_t s2 = ((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y + 1) + m_seed);
////        std::uint64_t s3 = ((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y + 1) + m_seed);
////        std::uint64_t s4 = ((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y) + m_seed);
//
//
//        // each xy pair turns into distance vector from respective corner, corner zero is our starting corner (bottom
//        // left)
//
//        corner_0_contrib = glm::dot(grad(corner_x, corner_y), {dist_x, dist_y});
//
//
//        corner_1_contrib = glm::dot(grad(corner_x, corner_y+1), {dist_x, dist_y - 1});
//
//
//
//        corner_2_contrib = glm::dot(grad(corner_x+1, corner_y+1), {dist_x - 1, dist_y - 1});
//
//
//
//        corner_3_contrib = glm::dot(grad(corner_x+1, corner_y), {dist_x - 1, dist_y});
//
//
//        double u = nonLinearActivationFunction(dist_x);
//        double v = nonLinearActivationFunction(dist_y);
//
//
//        double x_bottom = interpolate(corner_0_contrib, corner_3_contrib, u);
//        double x_top = interpolate(corner_1_contrib, corner_2_contrib, u);
//        double total_xy = interpolate(x_bottom, x_top, v);
//        return total_xy;
//    }
//};


//class GradientNoise {
//    std::mt19937_64 rng;
//    std::uint64_t m_seed;
//    std::uniform_int_distribution<std::uint8_t> distribution;
//    const std::array<glm::vec2, 4> vector_choice = {glm::vec2(1.0, 1.0), glm::vec2(-1.0, 1.0), glm::vec2(1.0, -1.0),
//                                                    glm::vec2(-1.0, -1.0)};
//
//public:
//    GradientNoise(uint64_t seed) {
//        m_seed = seed;
//        //rng.seed(m_seed);
//        distribution = std::uniform_int_distribution<std::uint8_t>(0, 3);
//    }
//
//    // 0 -> 1
//    double nonLinearActivationFunction(double value) {
//        //return value * value * value * (value * (value * 6.0 - 15.0) + 10.0);
//        return value;
//    }
//
//    // 0 -> 1
//    //replace activation with cosine interpolation?
//    double interpolate(double a, double b, double t) {
//        //return (1 - t) * a + t * b;
//        double mu2 = (1 - cos(t * M_PI)) / 2;
//        return (a * (1 - mu2) + b * mu2);
//    }
//
//    std::uint64_t xorShift64(std::uint64_t a) {
//        a ^= (a << 21);
//        a ^= (a >> 35);
//        a ^= (a << 4);
//        return a;
//    }
//
//    double noise(double x, double y) {
//        //first get the bottom left corner associated
//        // with these coordinates
//        int corner_x = std::floor(x);
//        int corner_y = std::floor(y);
//
//        // then get the respective distance from that corner
//        double dist_x = x - corner_x;
//        double dist_y = y - corner_y;
//
//        double corner_0_contrib; // bottom left
//        double corner_1_contrib; // top left
//        double corner_2_contrib; // top right
//        double corner_3_contrib; // bottom right
//
//        std::uint64_t s1 = ((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y) + m_seed);
//        std::uint64_t s2 = ((std::uint64_t(corner_x) << 32) + std::uint64_t(corner_y + 1) + m_seed);
//        std::uint64_t s3 = ((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y + 1) + m_seed);
//        std::uint64_t s4 = ((std::uint64_t(corner_x + 1) << 32) + std::uint64_t(corner_y) + m_seed);
//
//
//        std::uint64_t tempy;
//        std::uint64_t mix;
//        std::uint64_t result;
//        // each xy pair turns into distance vector from respective corner, corner zero is our starting corner (bottom
//        // left)
//
//        std::uint64_t modparam = 7;
//        std::uint64_t andparam = 3;
//        tempy = xorShift64(corner_y);
//        mix = xorShift64(corner_x) + ((tempy << 32) + (tempy >> 32)) + 0xCAFEBABE;
//        result = (xorShift64(mix) % modparam)& andparam;
//        corner_0_contrib = glm::dot(vector_choice[result], {dist_x, dist_y});
//
//        tempy = xorShift64(corner_y + 1);
//        mix = xorShift64(corner_x) + ((tempy << 32) + (tempy >> 32)) + 0xCAFEBABE;
//        result = (xorShift64(mix) % modparam)& andparam;
//        corner_1_contrib = glm::dot(vector_choice[result], {dist_x, dist_y - 1});
//
//
//        tempy = xorShift64(corner_y+1);
//        mix = xorShift64(corner_x+1) + ((tempy << 32) + (tempy >> 32)) + 0xCAFEBABE;
//        result = (xorShift64(mix) % modparam)& andparam;
//        corner_2_contrib = glm::dot(vector_choice[result], {dist_x - 1, dist_y - 1});
//
//
//        tempy = xorShift64(corner_y);
//        mix = xorShift64(corner_x+1) + ((tempy << 32) + (tempy >> 32)) + 0xCAFEBABE;
//        result = (xorShift64(mix) % modparam)& andparam;
//        corner_3_contrib = glm::dot(vector_choice[result], {dist_x - 1, dist_y});
//
//
//        double u = nonLinearActivationFunction(dist_x);
//        double v = nonLinearActivationFunction(dist_y);
//
//
//        double x_bottom = interpolate(corner_0_contrib, corner_3_contrib, u);
//        double x_top = interpolate(corner_1_contrib, corner_2_contrib, u);
//        double total_xy = interpolate(x_bottom, x_top, v);
//        return total_xy;
//    }
//};


#endif //GLPROJECT_GRADIENTNOISE_H
