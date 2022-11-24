#pragma once

#include <cstdint>
#include <utility>

namespace coords {
    struct CoordGenerator {
    public:
        explicit CoordGenerator(double rotation);

        std::pair<float, float> GetCoords();

    private:
        float x, y;
        double sin_phi, cos_phi;
    };
}
