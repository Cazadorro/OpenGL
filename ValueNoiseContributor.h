//
// Created by Shae Bolt on 7/22/2017.
//

#ifndef GLPROJECT_VALUEPRNGINDEXHASH_H
#define GLPROJECT_VALUEPRNGINDEXHASH_H

#include <array>

#include <cstdint>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ValuePrngIndexHash {

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
        return ((m_prng_hasher.hash32bit2D(x, y, offset) & 255));
    }
};

#endif //GLPROJECT_VALUEPRNGINDEXHASH_H
