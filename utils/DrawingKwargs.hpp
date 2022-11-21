#pragma once

#include <string>

namespace kwargs {
    enum DrawingApi {
        SFML,
        SDL
    };
    enum GraphType {
        ADJACENCY,
        EDGES
    };
    struct DrawingKwargs {
        DrawingApi api;
        GraphType graph_type;
        std::string graph_path;
    };
}
