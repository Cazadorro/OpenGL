//
// Created by Shae Bolt on 7/15/2017.
//

#ifndef GLPROJECT_OCTAVENOISE_H
#define GLPROJECT_OCTAVENOISE_H

#include <cmath>
typedef double (*Activator)(double);
typedef double (*Interpolator)(double,double,double);
template<class Contributor, Activator activator, Interpolator interpolator>
class OctaveNoise {
    Contributor m_contributor;
public:

    OctaveNoise(const Contributor &contributor) :
            m_contributor(contributor) {};

    double noise(double x, double y) {
        int corner_x = std::floor(x);
        int corner_y = std::floor(y);

        // then get the respective distance from that corner
        double dist_x = x - corner_x;
        double dist_y = y - corner_y;

        double corner_0_contrib; // bottom left
        double corner_1_contrib; // top left
        double corner_2_contrib; // top right
        double corner_3_contrib; // bottom right

        corner_0_contrib = m_contributor(x, y, dist_x, dist_y);
        corner_1_contrib = m_contributor(x, y + 1, dist_x, dist_y - 1.0);
        corner_2_contrib = m_contributor(x + 1, y + 1, dist_x - 1.0, dist_y - 1.0);
        corner_3_contrib = m_contributor(x + 1, y, dist_x - 1.0, dist_y);

        double u = activator(dist_x);
        double v = activator(dist_y);

        double x_bot_interp = interpolator(corner_0_contrib, corner_3_contrib, u);
        double x_top_interp = interpolator(corner_1_contrib, corner_2_contrib, u);
        double xandy_interp = interpolator(x_bot_interp, x_top_interp, v);
        return xandy_interp;
    };

};


#endif //GLPROJECT_OCTAVENOISE_H
