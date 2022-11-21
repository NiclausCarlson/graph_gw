#include "GraphDrawing.hpp"
#include "sfml/SFMLDrawing.hpp"
#include "sdl/SDLDrawing.hpp"

namespace drawing {

    GraphDrawing::GraphDrawing(const kwargs::DrawingApi &api) {
        if (api == kwargs::SFML) {
            abstract_drawing = std::make_unique<impl::SFMLDrawing>();
        }
        abstract_drawing = std::make_unique<impl::SDLDrawing>();
    }

    void GraphDrawing::Draw(const graph::Graph &graph) {
        abstract_drawing->Draw();
    }

}
