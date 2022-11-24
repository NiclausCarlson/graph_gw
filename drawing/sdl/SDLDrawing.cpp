#include "SDLDrawing.hpp"

#include "../Config.hpp"

namespace drawing::impl {

    SDLDrawing::SDLDrawing(const SDlDrawSettings &settings) :
            window(settings),
            point_ctx(-2 * M_PI / settings.vertex_count),
            settings(settings) {}

    void SDLDrawingImpl::SDLWindowDestroyer::operator()(SDL_Window *w) const {
        SDL_DestroyWindow(w);
    }

    void SDLDrawingImpl::SDLRendererDestroyer::operator()(SDL_Renderer *w) const {
        SDL_DestroyRenderer(w);
    }

    void SDLDrawingImpl::TTFFontDestroyer::operator()(TTF_Font *w) const {
        TTF_CloseFont(w);
    }

    void SDLDrawingImpl::SDLTextureDestroyer::operator()(SDL_Texture *w) const {
        SDL_DestroyTexture(w);
    }

    SDLDrawingImpl::SDLDrawingImpl(const SDlDrawSettings &draw_settings) : is_running(true),
                                                                           vertex_color(draw_settings.vertex_color),
                                                                           edge_color(draw_settings.edge_color),
                                                                           font_color(draw_settings.font_color) {
        OnInit(draw_settings);
    }

    void SDLDrawingImpl::OnInit(const SDlDrawSettings &draw_settings) {
        TTF_Init();
        font.reset(TTF_OpenFont(config::kFontPath.c_str(), config::kTextSize));
        if (!font) {
            throw std::runtime_error(TTF_GetError());
        }

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            throw std::runtime_error(std::string("Can't init SDL: ") + SDL_GetError());
        }

        window.reset(SDL_CreateWindow(draw_settings.title.c_str(),
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      config::kWidth, config::kHeight,
                                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE));

        if (!window) {
            throw std::runtime_error(std::string("Can't initialize window: ") + SDL_GetError());
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
            if (!font) return 1;
            SetColor(font_color);
            SDL_RenderClear(renderer.get());
            SetColor(edge_color);

            for (const auto &it: edges) {
                auto res = SDL_RenderDrawLine(renderer.get(), it.a.x, it.a.y,
                                              it.b.x, it.b.y);
                if (res != 0) {
                    throw std::runtime_error("Can't render edge");
                }
            }

            for (const auto &it: vertexes) {
                const auto &v = it.second.vertex.points;
                SetColor(font_color);
                auto begin = v.begin();
                auto mid = begin + v.size() / 2;
                auto end = v.end() - 1;
                for (; begin != mid; ++begin) {
                    auto res = SDL_RenderDrawLine(renderer.get(),
                                                  begin->x, begin->y - 1,
                                                  end->x, end->y);
                    if (res != 0) {
                        throw std::runtime_error("Can't render circle");
                    }
                    --end;
                }

                SetColor(vertex_color);
                for (const auto &point: v) {
                    auto [x, y] = point;
                    auto res = SDL_RenderDrawPoint(renderer.get(), x, y);
                    if (res != 0) {
                        throw std::runtime_error("Can't render circle");
                    }
                }
                std::unique_ptr<SDL_Texture, SDLTextureDestroyer> text;
                text.reset(RenderText(std::to_string(it.second.id),
                                      SDL_Color{0x00, 0x00, 0x00, 0x00}));
                const auto &[x, y] = it.second.vertex.center;
                const auto rect = SDL_Rect{(int) x, (int) y, 20, 20};
                SDL_RenderCopy(renderer.get(), text.get(), nullptr, &rect);
            }

            SDL_RenderPresent(renderer.get());
        }
        return 0;
    }

    SDL_Texture *
    SDLDrawingImpl::RenderText(const std::string &message, SDL_Color color) {

        SDL_Surface *surf = TTF_RenderText_Blended(font.get(), message.c_str(), color);
        if (surf == nullptr) {
            return nullptr;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.get(), surf);
        if (texture == nullptr) {
            throw std::runtime_error("Can't create text texture");
        }

        SDL_FreeSurface(surf);
        return texture;
    }

    void SDLDrawingImpl::SetColor(Color color) {
        switch (color) {
            case kBlack:
                SDL_SetRenderDrawColor(renderer.get(), 0x00, 0x00, 0x00, 0x00);
                break;
            case kWhite:
                SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
                break;
        }
    }


    void SDLDrawing::AddCircle(const uint32_t &vertx_id) {
        auto [x, y] = point_ctx.GetCoords();
        vertexes.insert({vertx_id, {vertx_id,
                                    sdl2_primitives::Circle(x, y, config::kVertexRadius)}});
    }

    void SDLDrawing::AddLine(uint32_t u, uint32_t v) {
        const auto &vert_u = vertexes.at(u).vertex.center;
        const auto &vert_v = vertexes.at(v).vertex.center;
        edges.push_back({{vert_u.x, vert_u.y},
                         {vert_v.x, vert_v.y}});
    }

    void SDLDrawing::Draw() {
        if (const auto res = window.Execute(vertexes, edges); res != 0) {
            throw std::runtime_error("Can't use SDl");
        }
    }

}
