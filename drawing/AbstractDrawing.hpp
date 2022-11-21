#pragma once

#include <cstdint>
#include <string>

namespace drawing::impl {
    struct AbstractDrawing {
        virtual void DrawCircle() = 0;

        virtual void DrawLine() = 0;

        virtual void Draw() = 0;

        virtual ~AbstractDrawing() = default;
    };

    struct DrawSettings {
        uint32_t height, width;
        std::string title;
    };
}
