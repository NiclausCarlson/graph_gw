#include "SDLDrawing.hpp"


namespace drawing::impl {

    SDLDrawing::SDLDrawing(const SDlDrawSettings &settings) :
            window(settings),
            point_ctx(settings.width,
                      settings.height,
                      -2 * M_PI / settings.vertex_count,
                      settings.radius),
            settings(settings) {}

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

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            throw std::runtime_error(std::string("Can't init SDL: ") + SDL_GetError());
        }

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

            SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(renderer.get());
            SDL_SetRenderDrawColor(renderer.get(), 0x00, 0x00, 0x00, 0x00);

            for (const auto &it: vertexes) {
                for (const auto &point: it.second.vertex.points) {
                    auto [x, y] = point;
                    auto res = SDL_RenderDrawPoint(renderer.get(), x, y);
                    if (res != 0) {
                        throw std::runtime_error("Can't render circle");
                    }
                }
            }

            for (const auto &it: edges) {

            }

            SDL_RenderPresent(renderer.get());
        }
        return 0;
    }


    void SDLDrawing::AddCircle(const uint32_t &vertx_id) {
        auto [x, y] = point_ctx.GetCoords();
        vertexes.insert({vertx_id, {vertx_id,
                                    sdl2_primitives::Circle(x, y, settings.radius)}});
    }

    void SDLDrawing::AddLine(uint32_t u, uint32_t v) {

    }

    void SDLDrawing::Draw() {
        if (const auto res = window.Execute(vertexes, edges); res != 0) {
            throw std::runtime_error("Can't use SDl");
        }
    }

}
