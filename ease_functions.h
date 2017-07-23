//
// Created by Shae Bolt on 7/22/2017.
//

#ifndef GLPROJECT_EASEFUNCTIONS_H
#define GLPROJECT_EASEFUNCTIONS_H

#include <cstdint>
#include <cmath>

// If values between 0 and 1,
// output between 0 and 1
namespace ease {
    namespace private_ {
        typedef double (*EaseT)(double);

        template<EaseT inFunction, EaseT outFunction>
        double inOut(double value) {
            if (value < 0.5) {
                return inFunction(value * 2) / 2;
            }
            return (outFunction(value * 2 - 1) / 2) + 0.5;
        };

        template<std::intmax_t A>
        double exponentTemplate(double value) {
            return (exp(A * value) - 1) / (exp(A) - 1);
        }
    }

    double perlin(double value);

    double linear(double value);

    double sineIn(double value);

    double sineOut(double value);

    double sineInOut(double value);

    double circleIn(double value);

    double circleOut(double value);

    double circleInOut(double value);

    template<std::size_t N>
    double polynomialIn(double value) {
        return pow(value, N);
    }

    template<std::size_t N>
    double polynomialOut(double value) {
        return 1 - pow(value - 1, N);
    }

    template<std::size_t N>
    double polynomialInOut(double value) {
        if (value < 0.5) {
            return polynomialIn<N>(value * 2) / 2;
        }
        return (polynomialOut<N>(value * 2 - 1) / 2) + 0.5;
    }
    //constexpr auto  polynomialInOut = private_::inOut<polynomialIn, polynomialOut>;

    template<std::intmax_t A>
    double exponentIn(double value) {
        return private_::exponentTemplate<A>(value);
    }

    template<std::intmax_t A>
    double exponentOut(double value) {
        return private_::exponentTemplate<-A>(value);
    }

    template<std::intmax_t A>
    double exponentInOut(double value) {
        if (value < 0.5) {
            return exponentIn<A>(value * 2) / 2;
        }
        return (exponentOut<A>(value * 2 - 1) / 2) + 0.5;
    }


}


#endif //GLPROJECT_EASEFUNCTIONS_H
