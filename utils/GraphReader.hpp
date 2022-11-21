#pragma once

#include "../models/Graph.hpp"
#include "../utils/DrawingKwargs.hpp"

namespace graph_reader {

    graph::Graph ReadGraph(const kwargs::DrawingKwargs& kwargs);

}
