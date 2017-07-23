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

    double sineIn(double value) {
        return 1 + sin(M_PI / 2 * value - M_PI / 2);
    }

    double sineOut(double value) {
        return sin(M_PI / 2 * value);
    }

    double sineInOut(double value) {
        return (1 + sin(M_PI * value - M_PI / 2)) / 2;
    }

    double circleIn(double value) {
        return 1 - sqrt(1 - pow(value, 2));
    }


    double circleOut(double value) {
        return (sqrt(1 - pow((value - 1), 2)));
    }

    double circleInOut(double value) {
        if (value < 0.5) {
            return circleIn(value * 2) / 2;
        }
        return (circleOut(value * 2 - 1) / 2) + 0.5;
    }
}