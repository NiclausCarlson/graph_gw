#pragma once

#include "../AbstractDrawing.hpp"

#include <SDL2/SDL.h>
#include <string>
#include <memory>

namespace drawing::impl {

    struct SDlDrawSettings : public DrawSettings {
    };

    struct SDLWindowDestroyer {
        void operator()(SDL_Window *w) const;
    };

    class SDLDrawing : public AbstractDrawing {
    public:
        explicit SDLDrawing(const SDlDrawSettings &draw_settings);

        void DrawCircle() override;

        void DrawLine() override;

        void Draw() override;

    private:
        std::unique_ptr<SDL_Window, SDLWindowDestroyer> window;
    };
}
