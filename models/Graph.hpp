#pragma once

#include <memory>
#include <vector>

namespace graph {
    class Graph {
    private:
        struct Vertex;

    public:
        explicit Graph(const uint32_t &vertex_count);

        void AddEdge(const uint32_t &start, const uint32_t &end);

        const std::vector<std::pair<Vertex, Vertex>> &GetEdges();

        uint32_t Size() const noexcept;

    private:
        struct Vertex {
            uint32_t id;

            bool operator==(const Vertex &other) const;
        };

        uint32_t vertex_count;
        std::vector<std::pair<Vertex, Vertex>> edges;
    };
}
