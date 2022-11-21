#include "GraphDrawing.hpp"
#include "sfml/SFMLDrawing.hpp"
#include "sdl/SDLDrawing.hpp"
#include <cmath>

namespace drawing {

    GraphDrawing::GraphDrawing(const kwargs::DrawingApi &api, graph::Graph &&graph) : graph(std::move(graph)) {
        const auto coeff = std::sqrt(this->graph.Size());
        uint32_t height = 600 * coeff;
        uint32_t width = 800 * coeff;
        if (api == kwargs::SFML) {
            abstract_drawing = std::make_unique<impl::SFMLDrawing>(
                    impl::SFMLDrawSettings{height, width, "Graph", graph.Size(), sf::Color::Yellow}
            );
        } else if (api == kwargs::SDL) {
            abstract_drawing = std::make_unique<impl::SDLDrawing>(
                    impl::SDlDrawSettings{height, width, "Graph", graph.Size()}
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
        abstract_drawing->Draw();
    }

}
