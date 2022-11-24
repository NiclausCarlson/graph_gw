#pragma once

#include <cstdint>
#include <vector>

namespace drawing::impl::sdl2_primitives {
    struct Point {
        int32_t x;
        int32_t y;
    };

    struct Circle {
        Circle(int32_t start_x, int32_t start_y);

        std::vector<Point> points;
        Point start_point;
    };

    struct Line {
        Point a;
        Point b;
    };
}
