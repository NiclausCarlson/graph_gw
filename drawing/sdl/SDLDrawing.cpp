#include "SDLDrawing.hpp"


namespace drawing::impl {

    SDLDrawing::SDLDrawing(const SDlDrawSettings &draw_settings) : window(draw_settings) {
    }

    void SDLDrawingImpl::SDLWindowDestroyer::operator()(SDL_Window *w) const {
        SDL_DestroyWindow(w);
    }

    void SDLDrawingImpl::SDLRendererDestroyer::operator()(SDL_Renderer *w) const {
        SDL_DestroyRenderer(w);
    }

    SDLDrawingImpl::SDLDrawingImpl(const SDlDrawSettings &draw_settings) : is_running(true) {
        OnInit(draw_settings);
    }

    void SDLDrawingImpl::OnInit(const SDlDrawSettings &draw_settings) {
        window.reset(SDL_CreateWindow(draw_settings.title.c_str(),
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      draw_settings.width, draw_settings.height,
                                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE));

        if (!window) {
            throw std::runtime_error("Can't initialize window");
        }

        renderer.reset(SDL_CreateRenderer(window.get(),
                                          -1,
                                          SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));

        if (!renderer) {
            throw std::runtime_error("Can't initialize rendered");
        }
    }

    void SDLDrawingImpl::OnEvent(const SDL_Event &event) {
        if (event.type == SDL_QUIT) {
            is_running = false;
        }
    }

    int SDLDrawingImpl::Execute(const std::unordered_map<uint32_t, SDlVertexDescriptor> &vertexes,
                                const std::vector<sdl2_primitives::Line> &edges) {
        SDL_Event event;
        while (is_running) {
            while (SDL_PollEvent(&event)) {
                OnEvent(event);
            }
            if (!window) return 1;
            if (!renderer) return 1;
            SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 0);

            for (const auto &it: vertexes) {

            }

            for (const auto &it: edges) {

            }

            SDL_RenderClear(renderer.get());
            SDL_RenderPresent(renderer.get());
        }
        return 0;
    }


    void SDLDrawing::AddCircle(const uint32_t &vertx_id) {

    }

    void SDLDrawing::AddLine(uint32_t u, uint32_t v) {

    }

    void SDLDrawing::Draw() {
        if (const auto res = window.Execute(vertexes, edges); res != 0) {
            throw std::runtime_error("Can't use SDl");
        }
    }

}
