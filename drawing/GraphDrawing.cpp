#include "GraphDrawing.hpp"
#include "sfml/SFMLDrawing.hpp"
#include "sdl/SDLDrawing.hpp"
#include <cmath>

namespace drawing {

    GraphDrawing::GraphDrawing(const kwargs::DrawingApi &api, graph::Graph &&graph) : graph(std::move(graph)) {
        const float height = 1024, width = 1280;
        const float radius = 40.0f;
        const uint32_t border_width = 10;
        const uint32_t char_size = 24;
        if (api == kwargs::SFML) {
            abstract_drawing = std::make_unique<impl::SFMLDrawing>(
                    impl::SFMLDrawSettings{
                            height,
                            width,
                            "Graph",
                            graph.Size(),
                            radius,
                            sf::Color::White,
                            sf::Color::Black,
                            border_width,
                            char_size,
                            sf::Color::Black,
                    }
            );
        } else if (api == kwargs::SDL) {
            abstract_drawing = std::make_unique<impl::SDLDrawing>(
                    impl::SDlDrawSettings{
                            height,
                            width,
                            "Graph",
                            graph.Size(),
                            radius
                    }
            );
        }
    }

    void GraphDrawing::Draw() {
        if (!abstract_drawing) {
            throw std::runtime_error("Drawing api not found");
        }
        for (auto it = 1; it <= graph.Size(); ++it) {
            abstract_drawing->AddCircle(it);
        }
        for (const auto &it: graph.GetEdges()) {
            abstract_drawing->AddLine(it.first.id, it.second.id);
        }
        abstract_drawing->Draw();
    }

}
