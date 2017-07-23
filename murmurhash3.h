//
// Created by Shae Bolt on 7/17/2017.
//

#ifndef GLPROJECT_MURMURHASH3_H
#define GLPROJECT_MURMURHASH3_H

#include <cstdint>

class MurmurHash3 {
public:
    std::uint64_t hash32(std::uint32_t h);

    std::uint64_t hash64(std::uint64_t h);

    std::uint64_t hash128(const std::uint64_t &high, const std::uint64_t &low);

    std::uint64_t hash32bit1D(std::uint32_t a, std::uint64_t offset);

    std::uint64_t hash32bit2D(std::uint32_t a, std::uint32_t b, std::uint64_t offset);

    std::uint64_t hash32bit3D(std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint64_t offset);

    std::uint64_t hash32bit4D(std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d, std::uint64_t offset);

};

#endif //GLPROJECT_MURMURHASH3_H
