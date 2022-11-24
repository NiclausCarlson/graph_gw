#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../vertex_coord_generator/CoordGenerator.hpp"
#include "../AbstractDrawing.hpp"
#include "Primitives.hpp"


namespace drawing::impl {

    enum Color {
        kBlack,
        kWhite
    };

    struct SDlDrawSettings : public DrawSettings {
        Color vertex_color;
        Color edge_color;
        Color font_color;
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

        SDL_Texture *RenderText(const std::string &message, SDL_Color color);

        void SetColor(Color color);

        struct SDLWindowDestroyer {
            void operator()(SDL_Window *w) const;
        };

        struct SDLRendererDestroyer {
            void operator()(SDL_Renderer *w) const;
        };

        struct TTFFontDestroyer {
            void operator()(TTF_Font *w) const;
        };

        struct SDLTextureDestroyer {
            void operator()(SDL_Texture *w) const;
        };

        std::unique_ptr<SDL_Window, SDLWindowDestroyer> window;
        std::unique_ptr<SDL_Renderer, SDLRendererDestroyer> renderer;
        std::unique_ptr<TTF_Font, TTFFontDestroyer> font;
        bool is_running;

        Color vertex_color;
        Color edge_color;
        Color font_color;
    };

    class SDLDrawing : public AbstractDrawing {
    public:
        explicit SDLDrawing(const SDlDrawSettings &settings);

        void AddCircle(const uint32_t &vertx_id) override;

        void AddLine(uint32_t u, uint32_t v) override;

        void Draw() override;

    private:
        SDLDrawingImpl window;
        std::unordered_map<uint32_t, SDlVertexDescriptor> vertexes;
        std::vector<sdl2_primitives::Line> edges;
        coords::CoordGenerator point_ctx;
        SDlDrawSettings settings;
    };
}
