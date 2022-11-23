#include "CoordGenerator.hpp"
#include <cmath>


namespace coords {

    CoordGenerator::CoordGenerator(uint32_t width, uint32_t height,
                                   double rotation, uint32_t radius) :
            x(width - 6 * radius),
            y(height / 2),
            sin_phi(std::sin(rotation)),
            cos_phi(std::cos(rotation)),
            width(width),
            height(height),
            radius(radius) {

    }

    std::pair<float, float> CoordGenerator::GetCoords() {
        static const double shift_x = width / 2;
        static const double shift_y = height / 2 - 2.4 * radius;

        const float res_x = x, res_y = y;
        const float new_s_x = x - shift_x;
        const float new_s_y = y - shift_y;
        x = new_s_x * cos_phi - new_s_y * sin_phi + shift_x;
        y = new_s_x * sin_phi + new_s_y * cos_phi + shift_y;

        return {res_x, res_y};
    }
}

