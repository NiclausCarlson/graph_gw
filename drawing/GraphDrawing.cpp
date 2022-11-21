#include "GraphDrawing.hpp"
#include "sfml/SFMLDrawing.hpp"
#include "sdl/SDLDrawing.hpp"

namespace drawing {

    GraphDrawing::GraphDrawing(const kwargs::DrawingApi &api, graph::Graph &&graph) : graph(std::move(graph)) {
        if (api == kwargs::SFML) {
            abstract_drawing = std::make_unique<impl::SFMLDrawing>(
                    impl::SFMLDrawSettings{800, 600, "Graph"}
            );
        } else if (api == kwargs::SDL) {
            abstract_drawing = std::make_unique<impl::SDLDrawing>(
                    impl::SDlDrawSettings{800, 600, "Graph"}
            );
        }
    }

    void GraphDrawing::Draw() {
        if (!abstract_drawing) {
            throw std::runtime_error("Drawing api not found");
        }
        abstract_drawing->Draw();
    }

}
