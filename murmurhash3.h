//
// Created by Shae Bolt on 7/17/2017.
//

#ifndef GLPROJECT_MURMURHASH3_H
#define GLPROJECT_MURMURHASH3_H

#include "Hasher.h"
#include <cstdint>

class MurmurHash3_32bit : public HasherXY<MurmurHash3_32bit> {
public:
    std::uint64_t hashFunction(std::uint64_t h) {
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;
        return h;
    }
};

class MurmurHash3_64bit : public HasherXY<MurmurHash3_64bit> {
public:
    std::uint64_t hashFunction(std::uint64_t h) {
        h ^= h >> 33;
        h *= 0xff51afd7ed558ccd;
        h ^= h >> 33;
        h *= 0xc4ceb9fe1a85ec53;
        h ^= h >> 33;
        return h;
    }
};


class MurmurHash3 {
public:
    std::uint64_t hash32(std::uint32_t h) {
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;
        return h;
    }

    std::uint64_t hash64(std::uint64_t h) {
        h ^= h >> 33;
        h *= 0xff51afd7ed558ccd;
        h ^= h >> 33;
        h *= 0xc4ceb9fe1a85ec53;
        h ^= h >> 33;
        return h;
    }

    std::uint64_t hash128(const std::uint64_t &high, const std::uint64_t &low) {
        const std::uint64_t kMul = 0x9ddfea08eb382d69ULL;
        std::uint64_t a = (low ^ high) * kMul;
        a ^= (a >> 47);
        std::uint64_t b = (high ^ a) * kMul;
        b ^= (b >> 47);
        b *= kMul;
        return b;
    }

    //add offset, make template to have explicit cast to use each.

    std::uint64_t hash32bit1D(std::uint32_t a, std::uint64_t offset) {
        return hash32(static_cast<std::uint32_t>(a + offset));
    }

    std::uint64_t hash32bit2D(std::uint32_t a, std::uint32_t b, std::uint64_t offset) {
        return hash64(a + (std::uint64_t(b) << 32) + offset);
    }

    std::uint64_t hash32bit3D(std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint64_t offset){
        return hash128(c, a + (std::uint64_t(b) << 32) + offset);
    }

    std::uint64_t hash32bit4D(std::uint32_t a, std::uint32_t b, std::uint32_t c, std::uint32_t d, std::uint64_t offset){
        return hash128(c + (std::uint64_t(d) << 32), a + (std::uint64_t(b) << 32) + offset);
    }


};

#endif //GLPROJECT_MURMURHASH3_H
