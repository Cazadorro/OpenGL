//
// Created by Shae Bolt on 7/13/2017.
//

#include "simplexnoise.h"

SimplexNoise_octave::SimplexNoise_octave(int seed) {
    std::copy(p_supply.begin(), p_supply.end(), p.begin());
    if (seed == RANDOMSEED) {
        m_seed = std::random_device()();
    }
    //the random for the swaps
    rng.seed(m_seed);
    //std::mt19937_64::result_type
    std::uniform_int_distribution<std::uint8_t> distribution(0, 255);
    //the seed determines the swaps that occur between the default order and the order we're actually going to use
    // theres actually a name for this?  isn't this a type of sampling?  Fisher yates shuffle?
    for (int i = 0; i < NUMBEROFSWAPS; i++) {
        int swapFrom = distribution(rng);
        int swapTo = distribution(rng);
        std::swap(p[swapFrom], p[swapTo]);
    }


    for (int i = 0; i < 512; i++) {
        perm[i] = p[i & 255];
        permMod12[i] =  (perm[i] % static_cast<std::uint8_t>(12));
    }
}


double SimplexNoise_octave::noise(double quad_coord_x, double quad_coord_y) {
    // Noise contributions from the three corners
    double noise_contribution_0, noise_contribution_1, noise_contribution_2;
    // Skew the input space to determine which simplex cell we're in
    // Skew the input space along the main diagonal
    double skew_factor = (quad_coord_x + quad_coord_y) * skew_coef; // Hairy factor for 2D
    int simplex_coord_i = std::floor(quad_coord_x + skew_factor);
    int simplex_coord_j = std::floor(quad_coord_y + skew_factor);
    // Get distances from the cell origin
    double unskew_factor = (simplex_coord_i + simplex_coord_j) * unskew_coef;
    double unskewed_x = simplex_coord_i - unskew_factor;
    double unskewed_y = simplex_coord_j - unskew_factor;
    // Get distances from the cell origin
    double simplex_x0_dist = quad_coord_x - unskewed_x;
    double simplex_y0_dist = quad_coord_y - unskewed_y;
    // For the 2D case, the simplex shape is an equilateral triangle.
    // Determine which simplex we are in within the equilateral triangle.
    int i1, j1; // Offsets for second (middle) corner of simplex in (simplex_coord_i,simplex_coord_j) coords
    // lower triangle, XY order: (0,0)->(1,0)->(1,1)
    if (simplex_x0_dist > simplex_y0_dist) {
        i1 = 1;
        j1 = 0;
    }// upper triangle, YX order: (0,0)->(0,1)->(1,1)
    else {
        i1 = 0;
        j1 = 1;

    }
    // A step of (1,0) in (simplex_coord_i,simplex_coord_j) means a step of (1-c,-c) in (x,y), and
    // a step of (0,1) in (simplex_coord_i,simplex_coord_j) means a step of (-c,1-c) in (x,y), where
    // c = (3-sqrt(3))/6

    double x1 = simplex_x0_dist - i1 + unskew_coef; // Offsets for middle corner in (x,y) unskewed coords
    double y1 = simplex_y0_dist - j1 + unskew_coef;
    double x2 = simplex_x0_dist - 1.0 + 2.0 * unskew_coef; // Offsets for last corner in (x,y) unskewed coords
    double y2 = simplex_y0_dist - 1.0 + 2.0 * unskew_coef;
    // Work out the hashed gradient indices of the three simplex corners
    int ii = simplex_coord_i & 255;
    int jj = simplex_coord_j & 255;
    int gi0 = permMod12[ii + perm[jj]];
    int gi1 = permMod12[ii + i1 + perm[jj + j1]];
    int gi2 = permMod12[ii + 1 + perm[jj + 1]];
    // Calculate the contribution from the three corners
    double t0 = 0.5 - simplex_x0_dist * simplex_x0_dist - simplex_y0_dist * simplex_y0_dist;
    if (t0 < 0){
        noise_contribution_0 = 0.0;
    }
    else {
        // (x,y) of grad3 used for 2D gradient
        t0 *= t0;
        noise_contribution_0 = t0 * t0 * glm::dot(glm::vec2(grad3[gi0]), {simplex_x0_dist, simplex_y0_dist});
    }
    double t1 = 0.5 - x1 * x1 - y1 * y1;
    if (t1 < 0) {
        noise_contribution_1 = 0.0;
    }
    else {
        t1 *= t1;
        noise_contribution_1 = t1 * t1 * glm::dot(glm::vec2(grad3[gi1]), {x1, y1});
    }
    double t2 = 0.5 - x2 * x2 - y2 * y2;
    if (t2 < 0) {
        noise_contribution_2 = 0.0;
    }
    else {
        t2 *= t2;
        noise_contribution_2 = t2 * t2 * glm::dot(glm::vec2(grad3[gi2]), {x2, y2});
    }
    // Add contributions from each corner to get the final noise value.
    // The result is scaled to return values in the interval [-1,1].
    return 70.0 * (noise_contribution_0 + noise_contribution_1 + noise_contribution_2);
}
