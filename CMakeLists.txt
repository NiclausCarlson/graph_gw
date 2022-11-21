cmake_minimum_required(VERSION 3.23)
project(graph)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

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
        drawing/GraphDrawing.hpp)

target_link_libraries(graph sfml-graphics sfml-audio)
