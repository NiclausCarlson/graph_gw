#pragma once

#include <memory>

#include "AbstractDrawing.hpp"
#include "../models/Graph.hpp"
#include "../utils/DrawingKwargs.hpp"

namespace drawing {
    class GraphDrawing {
    public:
        GraphDrawing(const kwargs::DrawingApi &api, graph::Graph &&graph);

        void Draw();

    private:
        std::unique_ptr<impl::AbstractDrawing> abstract_drawing;
        graph::Graph graph;
    };
}
