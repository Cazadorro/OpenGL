//
// Created by Shae Bolt on 7/15/2017.
//

#include "contrib_active_interp.h"

double nonLinearActivationFunction(double value) {
    return value * value * value * (value * (value * 6.0 - 15.0) + 10.0);
    //return 6*value*value*value*value*value - 15*value*value*value*value + 10*value*value*value;
}

double linearActivationFunction(double value) {
    return value;
}

double cosineInterpolate(double a, double b, double t) {
    double mu2 = (1 - cos(t * M_PI)) / 2;
    return (a * (1 - mu2) + b * mu2);
}

double linearInterpolate(double a, double b, double t) {
    return (1 - t) * a + t * b;
}


void Xorshift128plus::seed2(std::uint64_t a, std::uint64_t b) {
    m_seed[0] = a;
    m_seed[1] = b;
}

void Xorshift128plus::seed(std::uint64_t a) {
    seed2(123456788957ULL, a);
}

void Xorshift128plus::seed(std::uint32_t x, std::uint32_t y, std::uint64_t offset) {
    seed(((std::uint64_t(x)) + (std::uint64_t(y) << 32) + offset));
    std::uint64_t a = this->operator()();
    std::uint64_t b = this->operator()();
    seed2(a, b);
}

std::uint64_t Xorshift128plus::operator()() {
    std::uint64_t x = m_seed[0];
    const std::uint64_t y = m_seed[1];
    m_seed[0] = y;
    x ^= x << 23; // a
    m_seed[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
    return m_seed[1] + y;
}

std::uint64_t Xorshift128plus::operator()(std::uint64_t a) {
    seed(a);
    return this->operator()();
}

std::uint64_t Xorshift128plus::operator()(std::uint32_t x, std::uint32_t y, std::uint64_t offset) {
    seed(x, y, offset);
    return this->operator()();
}

void Xorshift64::seed(std::uint64_t a) {
    m_seed = a;
}

void Xorshift64::seed(std::uint32_t x, std::uint32_t y, std::uint64_t offset) {
    std::uint64_t tempy = this->operator()(y);
    std::uint64_t mix = this->operator()(x) + ((tempy << 32) + (tempy >> 32)) + 0xCAFEBABE + offset;
    seed(mix);
}

std::uint64_t Xorshift64::operator()() {
    m_seed ^= (m_seed << 21);
    m_seed ^= (m_seed >> 35);
    m_seed ^= (m_seed << 4);
    return m_seed;
}

std::uint64_t Xorshift64::operator()(std::uint64_t a) {
    seed(a);
    return this->operator()();
}

std::uint64_t Xorshift64::operator()(std::uint32_t x, std::uint32_t y, std::uint64_t offset) {
    seed(x, y, offset);
    return this->operator()();
}


void XorTestHash::seed(std::uint64_t a) {
    m_seed = a;
}

void XorTestHash::seed(std::uint32_t x, std::uint32_t y, std::uint64_t offset) {
    std::uint64_t mix = x + (std::uint64_t(y) << 32) + offset;
    seed(mix);
}

std::uint64_t XorTestHash::operator()() {
    m_seed = (m_seed ^ 61) ^ (m_seed >> 16);
    m_seed = m_seed + (m_seed << 3);
    m_seed = m_seed ^ (m_seed >> 4);
    m_seed = m_seed * 0x27d4eb2d;
    m_seed = m_seed ^ (m_seed >> 15);
    return m_seed;
}

std::uint64_t XorTestHash::operator()(std::uint64_t a) {
    seed(a);
    return this->operator()();
}

std::uint64_t XorTestHash::operator()(std::uint32_t x, std::uint32_t y, std::uint64_t offset) {
    seed(x, y, offset);
    return this->operator()();
}

void Xor64TestHash::seed(std::uint64_t a) {
    m_seed = a;
}

void Xor64TestHash::seed(std::uint32_t x, std::uint32_t y, std::uint64_t offset) {
    std::uint64_t mix = x + (std::uint64_t(y) << 32) + offset;
    seed(mix);
}

std::uint64_t Xor64TestHash::operator()() {
    m_seed = (~m_seed) + (m_seed << 21); // key = (key << 21) - key - 1;
    m_seed = m_seed ^ (m_seed >> 24);
    m_seed = (m_seed + (m_seed << 3)) + (m_seed << 8); // key * 265
    m_seed = m_seed ^ (m_seed >> 14);
    m_seed = (m_seed + (m_seed << 2)) + (m_seed << 4); // key * 21
    m_seed = m_seed ^ (m_seed >> 28);
    m_seed = m_seed + (m_seed << 31);
    return m_seed;
}

std::uint64_t Xor64TestHash::operator()(std::uint64_t a) {
    seed(a);
    return this->operator()();
}

std::uint64_t Xor64TestHash::operator()(std::uint32_t x, std::uint32_t y, std::uint64_t offset) {
    seed(x, y, offset);
    return this->operator()();
}


void LinearCongruentialGen64::seed(std::uint64_t seed) {
    rng.seed(seed);
}

void LinearCongruentialGen64::seed(std::uint32_t x, std::uint32_t y, std::uint64_t offset) {
    seed(((std::uint64_t(x)) + (std::uint64_t(y) << 32) + offset));
}

std::uint64_t LinearCongruentialGen64::operator()() {
    return distribution(rng);
}

std::uint64_t LinearCongruentialGen64::operator()(std::uint64_t a) {
    seed(a);
    return this->operator()();
}

std::uint64_t LinearCongruentialGen64::operator()(std::uint32_t x, std::uint32_t y, std::uint64_t offset) {
    seed(x, y, offset);
    return this->operator()();
}


void MersenneTwisterGen64::seed(std::uint64_t seed) {
    rng.seed(seed);
}

void MersenneTwisterGen64::seed(std::uint32_t x, std::uint32_t y, std::uint64_t offset) {
    seed(((std::uint64_t(x)) + (std::uint64_t(y) << 32) + offset));
}

std::uint64_t MersenneTwisterGen64::operator()() {
    return distribution(rng);
}

std::uint64_t MersenneTwisterGen64::operator()(std::uint64_t a) {
    seed(a);
    return this->operator()();
}

std::uint64_t MersenneTwisterGen64::operator()(std::uint32_t x, std::uint32_t y, std::uint64_t offset) {
    seed(x, y);
    return this->operator()();
}
