#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "../AbstractDrawing.hpp"
#include "Primitives.hpp"

namespace drawing::impl {

    struct SDlDrawSettings : public DrawSettings {
    };

    struct SDlVertexDescriptor : public VertexDescriptor {
        sdl2_primitives::Circle vertex;
    };

    class SDLDrawingImpl {
    public:
        explicit SDLDrawingImpl(const SDlDrawSettings &draw_settings);

        int Execute(const std::unordered_map<uint32_t, SDlVertexDescriptor> &vertexes,
                    const std::vector<sdl2_primitives::Line> &edges);

    private:
        void OnInit(const SDlDrawSettings &draw_settings);

        void OnEvent(const SDL_Event &event);

        struct SDLWindowDestroyer {
            void operator()(SDL_Window *w) const;
        };

        struct SDLRendererDestroyer {
            void operator()(SDL_Renderer *w) const;
        };

        std::unique_ptr<SDL_Window, SDLWindowDestroyer> window;
        std::unique_ptr<SDL_Renderer, SDLRendererDestroyer> renderer;
        bool is_running;
    };

    class SDLDrawing : public AbstractDrawing {
    public:
        explicit SDLDrawing(const SDlDrawSettings &draw_settings);

        void AddCircle(const uint32_t &vertx_id) override;

        void AddLine(uint32_t u, uint32_t v) override;

        void Draw() override;

    private:
        SDLDrawingImpl window;
        std::unordered_map<uint32_t, SDlVertexDescriptor> vertexes;
        std::vector<sdl2_primitives::Line> edges;
    };
}
