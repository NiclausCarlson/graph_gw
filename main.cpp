#include <iostream>
#include "utils/ArgumentsParser.hpp"

int main(int32_t argc, char *argv[]) {
    const auto result = parser::Parse(argc, argv);
    if (!result) {
        std::cerr << "Invalid arguments: api should be `SFML` or"
                     " `SDL`; graph type should be `ADJACENCY` or `EDGES`.";
        return 1;
    }
    return 0;
}
