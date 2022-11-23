#pragma once

#include <cstdint>
#include <utility>

namespace coords {
    struct CoordGenerator {
    public:
        CoordGenerator(uint32_t width, uint32_t height,
                       double rotation, uint32_t radius);

        std::pair<float, float> GetCoords();

    private:
        float x, y;
        double sin_phi, cos_phi;
        uint32_t width, height, radius;
    };
}
