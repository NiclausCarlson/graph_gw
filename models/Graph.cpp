#include "Graph.hpp"

namespace graph {

    bool Graph::Vertex::operator==(const Graph::Vertex &other) const {
        return id == other.id;
    }

    std::size_t Graph::VertexHasher::operator()(const Graph::Vertex &key) const {
        return std::hash<uint32_t>()(key.id);
    }

    Graph::Graph(const uint32_t &vertex_count) : vertex_count(vertex_count) {
        for (uint32_t i = 0; i < vertex_count; ++i) {
            vertexes_without_edges.insert(Vertex{i});
        }
    }

    void Graph::AddEdge(const uint32_t &start, const uint32_t &end) {
        Vertex u{start}, v{end};
        if (const auto &it = edges.find(u); it != edges.end()) {
            if (it->second == v) {
                throw std::runtime_error("Found duplicated edges");
            }
        }
        if (u.id > vertex_count || v.id > vertex_count) {
            throw std::runtime_error("Vertex number is greater than vertex_count");
        }
        vertexes_without_edges.erase(u);
        vertexes_without_edges.erase(v);
        edges.insert({u, v});
    }

    uint32_t Graph::Size() const noexcept {
        return vertex_count;
    }

    const std::unordered_map<Graph::Vertex, Graph::Vertex, Graph::VertexHasher> &Graph::GetEdges() {
        return edges;
    }
}
