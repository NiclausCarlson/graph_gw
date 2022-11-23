#pragma once

#include <cstdint>
#include <vector>

namespace drawing::impl::sdl2_primitives {
    struct Point {
        int32_t x;
        int32_t y;
    };

    struct Circle {
        Circle(int32_t center_x, int32_t center_y, int32_t radius);

        std::vector<Point> points;
        Point center;
        int32_t radius;
    };

    struct Line {
        Point a;
        Point b;
    };
}
