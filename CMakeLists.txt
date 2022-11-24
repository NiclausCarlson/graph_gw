cmake_minimum_required(VERSION 3.23)
project(graph)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(SDL2 REQUIRED SDL2)
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)


add_executable(graph
        main.cpp
        utils/DrawingKwargs.hpp
        utils/ArgumentsParser.cpp
        utils/ArgumentsParser.hpp
        models/Graph.cpp
        models/Graph.hpp
        utils/GraphReader.cpp
        utils/GraphReader.hpp
        drawing/AbstractDrawing.hpp
        drawing/sfml/SFMLDrawing.cpp
        drawing/sfml/SFMLDrawing.hpp
        drawing/GraphDrawing.cpp
        drawing/GraphDrawing.hpp
        drawing/sdl/SDLDrawing.cpp
        drawing/sdl/SDLDrawing.hpp
        drawing/sdl/Primitives.cpp
        drawing/sdl/Primitives.hpp
        drawing/vertex_coord_generator/CoordGenerator.cpp
        drawing/vertex_coord_generator/CoordGenerator.hpp drawing/Config.hpp)

target_link_libraries(graph sfml-graphics sfml-audio SDL2 ${SDL2TTF_LIBRARIES})
