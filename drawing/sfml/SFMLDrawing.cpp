#define _USE_MATH_DEFINES

#include "SFMLDrawing.hpp"
#include <cmath>

namespace drawing::impl {
    SFMLDrawing::SFMLDrawing(const SFMLDrawSettings &settings) :
            settings(settings),
            point_ctx(settings.width - 6 * settings.vertex_radius,
                      settings.height / 2,
                      -2 * M_PI / settings.vertex_count
            ),
            window(sf::VideoMode(settings.width, settings.height),
                   settings.title) {
    }

    SFMLDrawing::PointCtx::PointCtx(float initial_x, float initial_y, double rotation) :
            x(initial_x), y(initial_y), sin_phi(std::sin(rotation)), cos_phi(std::cos(rotation)) {
    }

    void SFMLDrawing::AddCircle(const uint32_t &vertex_id) {
        auto [x, y] = NextCoord();
        vertexes.insert({vertex_id, {vertex_id, x, y}});
    }

    void SFMLDrawing::AddLine(uint32_t u, uint32_t v) {
        edges.emplace_back(u, v);
    }

    void SFMLDrawing::Draw() {
        std::vector<std::pair<sf::CircleShape, sf::Text>> shapes;
        std::vector<sf::VertexArray> lines;
        sf::Font font;

        if (!font.loadFromFile("fonts/Times New Roman.ttf")) {
            throw std::runtime_error("Can't find font for text");
        }

        for (const auto &it: vertexes) {
            const auto &vertex = it.second;
            sf::CircleShape shape(settings.vertex_radius);
            shape.setPosition(vertex.x, vertex.y);
            shape.setFillColor(settings.vertex_color);
            shape.setOutlineThickness(settings.border_width);
            shape.setOutlineColor(settings.outline_color);

            auto [left, top, width, height] = shape.getGlobalBounds();
            sf::Text text;
            text.setFont(font);
            text.setString(std::to_string(it.second.id));
            text.setCharacterSize(settings.char_size);
            text.setFillColor(settings.text_color);
            text.setPosition(left + width / 2 - settings.char_size / 2,
                             top + height / 2 - settings.char_size / 2);
            shapes.emplace_back(shape, text);
        }

        for (const auto &it: edges) {
            const auto &u = vertexes[it.first];
            const auto &v = vertexes[it.second];
            sf::VertexArray line(sf::LineStrip, 2);
            line[0].position = sf::Vector2f(u.x, u.y);
            line[0].color = sf::Color::Red;
            line[1].position = sf::Vector2f(v.x, v.y);
            line[1].color = sf::Color::Red;
        }

        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear(sf::Color::White);
            for (const auto &shape: shapes) {
                const auto &[circle, text] = shape;
                window.draw(circle);
                window.draw(text);
            }
            for (const auto &line: lines) {
                window.draw(line);
            }
            window.display();
        }

    }

    std::pair<float, float> SFMLDrawing::NextCoord() {
        static const double shift_x = settings.width / 2;
        static const double shift_y = settings.height / 2 - 2.4 * settings.vertex_radius;

        const float res_x = point_ctx.x, res_y = point_ctx.y;
        const float new_s_x = point_ctx.x - shift_x;
        const float new_s_y = point_ctx.y - shift_y;
        point_ctx.x = new_s_x * point_ctx.cos_phi - new_s_y * point_ctx.sin_phi + shift_x;
        point_ctx.y = new_s_x * point_ctx.sin_phi + new_s_y * point_ctx.cos_phi + shift_y;

        return {res_x, res_y};
    }


}
