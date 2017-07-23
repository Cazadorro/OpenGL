//
// Created by Shae Bolt on 7/22/2017.
//

#include "interpolation_functions.h"
#include <cmath>

namespace interp {
    double cosine(double a, double b, double t) {
        double mu2 = (1 - cos(t * M_PI)) / 2;
        return (a * (1 - mu2) + b * mu2);
    }

    double linear(double a, double b, double t) {
        return (1 - t) * a + t * b;
    }

    double linearFast(double a, double b, double t) {
        return a + t * (b - a);
    }
}