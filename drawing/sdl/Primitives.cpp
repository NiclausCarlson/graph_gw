#include "Primitives.hpp"
#include <cmath>
#include "../Config.hpp"

namespace drawing::impl::sdl2_primitives {

    Circle::Circle(int32_t start_x, int32_t start_y) : start_point({start_x, start_y}){
        const auto radius = config::kVertexRadius;
        for (uint32_t angle = 0; angle < 360; ++angle) {
            int32_t x = start_x + radius * std::cos(angle * M_PI / 180.0);
            int32_t y = start_y + radius * std::sin(angle * M_PI / 180.0) + radius;
            points.emplace_back(Point{x, y});
        }
    }
}
