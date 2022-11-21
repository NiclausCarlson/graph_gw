#include <iostream>
#include "utils/ArgumentsParser.hpp"
#include "utils/GraphReader.hpp"

int main(int32_t argc, char *argv[]) {
    const auto kwargs = parser::Parse(argc, argv);
    if (!kwargs) {
        std::cerr << "Invalid arguments: api should be `SFML` or"
                     " `SDL`; graph type should be `ADJACENCY` or `EDGES`.";
        return 1;
    }
    try {
        auto graph = graph_reader::ReadGraph(*kwargs);
    } catch (const std::runtime_error &error) {
        std::cerr << error.what();
        return 1;
    }
    return 0;
}
