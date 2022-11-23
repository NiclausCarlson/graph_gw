#include "Primitives.hpp"
#include <cmath>


namespace drawing::impl::sdl2_primitives {

    Circle::Circle(float center_x, float center_y, int32_t radius) : center({center_x, center_y}),
                                                                     radius(radius) {
        for (uint32_t angle = 0; angle < 360; ++angle) {
            float x = center_x + radius * std::cos(angle * M_PI / 180.0);
            float y = center_y + radius * std::sin(angle * M_PI / 180.0) + radius;
            points.emplace_back(Point{x, y});
        }
    }
}
