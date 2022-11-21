#include "GraphReader.hpp"
#include <fstream>

namespace graph_reader {
    namespace {
        std::ifstream OpenFile(const std::string &path) {
            std::ifstream fin(path);
            if (!fin.is_open()) {
                throw std::runtime_error("File not found");
            }
            return fin;
        }

        graph::Graph ReadEdges(const std::string &path) {
            auto fin = OpenFile(path);
            uint32_t vertex_count;
            fin >> vertex_count;
            graph::Graph result(vertex_count);
            while (fin) {
                uint32_t u, v;
                fin >> u >> v;
                result.AddEdge(u, v);
                fin.peek();
            }
            return result;
        }

        graph::Graph ReadAdjacency(const std::string &path) {
            auto fin = OpenFile(path);
            uint32_t vertex_count;
            fin >> vertex_count;
            graph::Graph result(vertex_count);
            uint32_t i = 1, j = 1;
            while (fin) {
                bool has_edge;
                fin >> has_edge;
                if (has_edge) {
                    result.AddEdge(i, j);
                }
                ++j;
                if (j > vertex_count) {
                    j = 1;
                    ++i;
                }
            }
            if(i > vertex_count){
                throw std::runtime_error("Invalid adjacency matrix!");
            }
            return result;
        }
    }

    graph::Graph ReadGraph(const kwargs::DrawingKwargs &kwargs) {
        if (kwargs.graph_type == kwargs::EDGES) {
            return ReadEdges(kwargs.graph_path);
        }
        return ReadAdjacency(kwargs.graph_path);
    }

}

