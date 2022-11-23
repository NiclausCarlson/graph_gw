#include "Graph.hpp"

namespace graph {

    bool Graph::Vertex::operator==(const Graph::Vertex &other) const {
        return id == other.id;
    }


    Graph::Graph(const uint32_t &vertex_count) : vertex_count(vertex_count) {
    }

    void Graph::AddEdge(const uint32_t &start, const uint32_t &end) {
        Vertex u{start}, v{end};
        edges.emplace_back(u, v);
    }

    uint32_t Graph::Size() const noexcept {
        return vertex_count;
    }

    const std::vector<std::pair<Graph::Vertex, Graph::Vertex>> &Graph::GetEdges() {
        return edges;
    }
}
