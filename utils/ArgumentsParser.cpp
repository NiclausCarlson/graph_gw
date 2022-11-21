#include "ArgumentsParser.hpp"
#include <string>

namespace parser {
    namespace {
        std::optional<kwargs::DrawingApi> ParseApi(std::string &&type) {
            std::transform(type.begin(), type.end(), type.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            if (type == "sfml") {
                return kwargs::DrawingApi::SFML;
            }
            if (type == "sdl") {
                return kwargs::DrawingApi::SDL;
            }
            return std::nullopt;
        }

        std::optional<kwargs::GraphType> ParseType(std::string &&type) {
            std::transform(type.begin(), type.end(), type.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            if (type == "adjacency") {
                return kwargs::GraphType::ADJACENCY;
            }
            if (type == "edges") {
                return kwargs::GraphType::EDGES;
            }
            return std::nullopt;
        }
    }

    std::optional<kwargs::DrawingKwargs> Parse(int32_t argc, char *argv[]) {

        if (argc != 3) return std::nullopt;
        auto api = ParseApi(std::string(argv[1]));
        auto graph_type = ParseType(std::string(argv[2]));

        if (!api || !graph_type) return std::nullopt;
        return {{*api, *graph_type}};
    }
}
