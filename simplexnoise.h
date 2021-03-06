//
// Created by Shae Bolt on 7/13/2017.
//

#ifndef GLPROJECT_SIMPLEXNOISE_H
#define GLPROJECT_SIMPLEXNOISE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <utility>
#include <array>
#include <random>

#include <cmath>

class SimplexNoise_octave {  // Simplex noise in 2D, 3D and 4D
    int RANDOMSEED = 0;
    int NUMBEROFSWAPS = 400;

    const std::array<glm::vec3, 12> grad3 = {
            glm::vec3(1.0, 1.0, 0.0), glm::vec3(-1.0, 1.0, 0.0), glm::vec3(1.0, -1.0, 0.0), glm::vec3(-1.0, -1.0, 0.0),
            glm::vec3(1.0, 0.0, 1.0), glm::vec3(-1.0, 0.0, 1.0), glm::vec3(1.0, 0.0, -1.0), glm::vec3(-1.0, 0.0, -1.0),
            glm::vec3(0.0, 1.0, 1.0), glm::vec3(0.0, -1.0, 1.0), glm::vec3(0.0, 1.0, -1.0), glm::vec3(0.0, -1.0, -1.0)
    };

    //this contains all the numbers between 0 and 255, these are put in a// random order depending upon the seed
    const std::array<std::uint8_t, 256> p_supply = {
            151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37,
            240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57,
            177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77,
            146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54,
            65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86,
            164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85,
            212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154,
            163, 70, 221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178,
            185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145,
            235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4,
            150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
    };

    std::array<std::uint8_t, 256> p;

    // To remove the need for index wrapping, double the permutation table length
    std::array<std::uint8_t, 512> perm;
    std::array<std::uint8_t, 512> permMod12;
    std::mt19937_64 rng;
    std::uint64_t m_seed;
public:
    SimplexNoise_octave(int seed);

    // Skewing and unskewing factors for 2, 3, and 4 dimensions
private:
    //converting from simplex to quad mesh.
    // x = (a-b) u + b (u+v) // x is quad coord u is simplex
    // y = (a-b) v + b (u+v) // y is quad coord v is simplex
    // a and b are the scaling factor, make a-b = 1 for simple calc
    // x = (1)u + b(u+v)
    // y = (1)v + b(u+v)
    // unskew_coef is the constant b
    // skew_coef is inverse transform of b
    static constexpr double skew_coef = 0.5 * (std::sqrt(3.0) - 1.0);
    static constexpr double unskew_coef = (3.0 - std::sqrt(3.0)) / 6.0;

    // This method is a *lot* faster than using (int)Math.floor(x)
//
//    static int fastfloor(double x) {
//        int xi = (int) x;
//        return x < xi ? xi - 1 : xi;
//    }

    // 2D simplex noise
public:
    double noise(double quad_coord_x, double quad_coord_y);

};


#endif //GLPROJECT_SIMPLEXNOISE_H
