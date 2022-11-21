#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>

namespace graph {
    class Graph {
    public:
        explicit Graph(const uint32_t &vertex_count);

        void AddEdge(const uint32_t& start, const uint32_t& end);

    private:
        struct Vertex {
            uint32_t id;

            bool operator==(const Vertex &other) const;
        };

        struct VertexHasher {
            std::size_t operator()(const Vertex &k) const;
        };

        uint32_t vertex_count;
        std::unordered_map<Vertex, Vertex, VertexHasher> edges;
        std::unordered_set<Vertex, VertexHasher> vertexes_without_edges;
    };
}
