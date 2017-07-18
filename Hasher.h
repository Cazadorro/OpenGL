//
// Created by Shae Bolt on 7/17/2017.
//

#ifndef GLPROJECT_HASHER_H
#define GLPROJECT_HASHER_H
#include <cstdint>

template<class Derived>
class HasherXY {
    std::uint64_t m_seed;
public:
    void seed(std::uint64_t a){
        m_seed = a;
    }

    void seed(std::uint32_t x, std::uint32_t y, std::uint64_t offset = 0){
        std::uint64_t mix = x + (std::uint64_t(y) << 32) + offset;
        seed(mix);
    }

    std::uint64_t operator()(){
        m_seed = static_cast<Derived*>(this)->hashFunction(m_seed);
        return m_seed;
    }

    std::uint64_t operator()(std::uint64_t a){
        seed(a);
        return this->operator()();
    }

    std::uint64_t operator()(std::uint32_t x, std::uint32_t y, std::uint64_t offset = 0){
        seed(x, y, offset);
        return this->operator()();
    }
};


#endif //GLPROJECT_HASHER_H
