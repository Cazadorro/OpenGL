//
// Created by Shae Bolt on 7/15/2017.
//

#ifndef GLPROJECT_OCTAVENOISE_H
#define GLPROJECT_OCTAVENOISE_H

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef double (*Activator)(double);

typedef double (*Interpolator)(double, double, double);

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

        corner_0_contrib = m_contributor(corner_x, corner_y, dist_x, dist_y);
        corner_1_contrib = m_contributor(corner_x, corner_y + 1, dist_x, dist_y - 1.0);
        corner_2_contrib = m_contributor(corner_x + 1, corner_y + 1, dist_x - 1.0, dist_y - 1.0);
        corner_3_contrib = m_contributor(corner_x + 1, corner_y, dist_x - 1.0, dist_y);

        double u = activator(dist_x);
        double v = activator(dist_y);

        double x_bot_interp = interpolator(corner_0_contrib, corner_3_contrib, u);
        double x_top_interp = interpolator(corner_1_contrib, corner_2_contrib, u);
        double xandy_interp = interpolator(x_bot_interp, x_top_interp, v);
        return xandy_interp;
    };

};


static constexpr double skew_coef = 0.5 * (std::sqrt(3.0) - 1.0);

glm::vec3 Barycentric(const glm::vec2 p, const glm::vec2 a, const glm::vec2 b, const glm::vec2 c);
template<class Contributor, Activator activator, Interpolator interpolator>
class BaryNoise {
    Contributor m_contributor;
public:

    BaryNoise(const Contributor &contributor) :
            m_contributor(contributor) {};

    double noise(double x, double y) {
        int corner_x = std::floor(x);
        int corner_y = std::floor(y);

        // then get the respective distance from that corner
        double dist_x = x - corner_x;
        double dist_y = y - corner_y;

        double skew_factor = (x + y) * skew_coef; // Hairy factor for 2D

        double skew_coord_x = x + skew_factor;
        double skew_coord_y = y + skew_factor;

        skew_coord_x -= std::floor(skew_coord_x);
        skew_coord_y -= std::floor(skew_coord_x);

        int simplex_coord_i = std::floor(x + skew_factor);
        int simplex_coord_j = std::floor(y + skew_factor);

        double corner_0_contrib; // bottom left
        double corner_1_contrib; // top left
        double corner_2_contrib; // top right
        double corner_3_contrib; // bottom right

        int corner_x1;
        int corner_y1;
        corner_0_contrib = m_contributor(corner_x, corner_y, dist_x, dist_y);
        if (dist_y > dist_x) {
            corner_1_contrib = m_contributor(corner_x, corner_y + 1.0, dist_x, dist_y - 1.0);
            corner_x1 = corner_x;
            corner_y1 = corner_y + 1;
        } else {
            corner_1_contrib = m_contributor(corner_x + 1.0, corner_y, dist_x - 1.0, dist_y);
            corner_x1 = corner_x + 1;
            corner_y1 = corner_y;
        }
        corner_2_contrib = m_contributor(corner_x + 1.0, corner_y + 1.0, dist_x - 1.0, dist_y - 1.0);

        glm::vec3 barycentric = Barycentric(glm::vec2(x, y), glm::vec2(corner_x, corner_y), glm::vec2(corner_x1, corner_y1),
                                            glm::vec2(corner_x + 1, corner_y + 1));

//        double u = activator(dist_x);
//        double v = activator(dist_y);

        double u = activator(barycentric.x);
        double v = activator(barycentric.y);
        double w = activator(barycentric.z);

        return (u * corner_0_contrib) + (v * corner_1_contrib) + (w * corner_2_contrib);


//        double x_bot_interp = interpolator(corner_0_contrib, corner_3_contrib, u);
//        double x_top_interp = interpolator(corner_1_contrib, corner_2_contrib, u);
//        double xandy_interp = interpolator(x_bot_interp, x_top_interp, v);
       // return xandy_interp;
    };

};




#endif //GLPROJECT_OCTAVENOISE_H
