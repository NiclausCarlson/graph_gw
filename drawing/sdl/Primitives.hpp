#pragma once

#include <cstdint>
#include <vector>

namespace drawing::impl::sdl2_primitives {
    struct Point {
        float x;
        float y;
    };

    struct Circle {
        Circle(float center_x, float center_y, int32_t radius);

        std::vector<Point> points;
        Point center;
        int32_t radius;
    };

    struct Line {
        Point a;
        Point b;
    };
}
