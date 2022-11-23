#include "Primitives.hpp"
#include <cmath>


namespace drawing::impl::sdl2_primitives {

    Circle::Circle(int32_t center_x, int32_t center_y, int32_t radius) : center({center_x, center_y}),
                                                                         radius(radius) {
        for (uint32_t angle = 0; angle < 360; ++angle) {
            int32_t x = center_x + radius * std::sin(angle * M_PI / 180.0);
            int32_t y = center_y + radius * std::cos(angle);
            points.emplace_back(Point{x, y});
        }
    }
}
