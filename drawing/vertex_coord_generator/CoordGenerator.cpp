#include "CoordGenerator.hpp"

#include <cmath>

#include "../Config.hpp"

namespace coords {
    namespace config = drawing::impl::config;

    CoordGenerator::CoordGenerator(double rotation) :
            x(config::kWidth - 6 * config::kVertexRadius),
            y(config::kHeight / 2),
            sin_phi(std::sin(rotation)),
            cos_phi(std::cos(rotation)) {

    }

    std::pair<float, float> CoordGenerator::GetCoords() {
        static const double shift_x = config::kWidth / 2;
        static const double shift_y = config::kHeight / 2 - 2.4 * config::kVertexRadius;

        const float res_x = x, res_y = y;
        const float new_s_x = x - shift_x;
        const float new_s_y = y - shift_y;
        x = new_s_x * cos_phi - new_s_y * sin_phi + shift_x;
        y = new_s_x * sin_phi + new_s_y * cos_phi + shift_y;

        return {res_x, res_y};
    }
}

