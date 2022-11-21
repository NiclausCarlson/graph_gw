#pragma once

#include <memory>

#include "AbstractDrawing.hpp"
#include "../models/Graph.hpp"
#include "../utils/DrawingKwargs.hpp"

namespace drawing {
    class GraphDrawing {
    public:
        explicit GraphDrawing(const kwargs::DrawingApi &api);

        void Draw(const graph::Graph &graph);

    private:
        std::unique_ptr<impl::AbstractDrawing> abstract_drawing;
    };
}
