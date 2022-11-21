#pragma once

#include <cstdint>

namespace drawing::impl {
    struct AbstractDrawing {
        virtual void DrawCircle() = 0;

        virtual void DrawLine() = 0;

        virtual void Draw() = 0;

        virtual ~AbstractDrawing() = default;
    };
}
