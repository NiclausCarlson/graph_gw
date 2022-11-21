#include "SFMLDrawing.hpp"
#include <cmath>

namespace drawing::impl {

    SFMLDrawing::SFMLDrawing(const SFMLDrawSettings &settings) :
            settings(settings),
            window(sf::VideoMode(settings.width,
                                 settings.height),
                   settings.title) {
    }


    void SFMLDrawing::AddCircle(const uint32_t &vertex_id) {
        const float radius = std::sqrt(settings.width * settings.height) / (settings.vertex_count * 3.0f);
        vertexes.insert({vertex_id, {vertex_id, radius, 500, 0}});
    }

    void SFMLDrawing::AddLine(uint32_t u, uint32_t v) {

    }

    void SFMLDrawing::Draw() {
        std::vector<sf::CircleShape> shapes;

        for (const auto &it: vertexes) {
            const auto &vertex = it.second;
            sf::CircleShape shape(vertex.radius);
            shape.setPosition(vertex.x, vertex.y);
            shape.setFillColor(settings.vertex_color);
            shapes.push_back(shape);
        }

        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            for (const auto &shape: shapes) {
                window.draw(shape);
            }
            window.display();
        }

    }

}
