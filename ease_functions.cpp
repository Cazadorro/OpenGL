//
// Created by Shae Bolt on 7/22/2017.
//

#include "ease_functions.h"

namespace ease {
    double perlin(double value) {
        return value * value * value * (value * (value * 6.0 - 15.0) + 10.0);
        //return 6*value*value*value*value*value - 15*value*value*value*value + 10*value*value*value;
    }

    double linear(double value) {
        return value;
    }
}