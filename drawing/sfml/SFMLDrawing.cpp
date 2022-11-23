#define _USE_MATH_DEFINES

#include "SFMLDrawing.hpp"
#include <cmath>

namespace drawing::impl {

    namespace {
        double GetDistance(const double &u_x, const double &u_y,
                           const double &v_x, const double &v_y) {
            return std::sqrt(std::pow(u_x - v_x, 2) + std::pow(u_y - v_y, 2));
        }

        double GetAngle(const double &u_x, const double &u_y,
                        const double &v_x, const double &v_y) {
            return std::atan2(v_y - u_y, v_x - u_x) * 180 / M_PI;
        }

        std::pair<double, double> CalcCenter(const sf::FloatRect &rect) {
            const auto [left, top, width, height] = rect;
            return {left + width / 2, top + height / 2};
        }
    }

    SFMLDrawing::SFMLDrawing(const SFMLDrawSettings &settings) :
            settings(settings),
            point_ctx(settings.width,
                      settings.height,
                      -2 * M_PI / settings.vertex_count,
                      settings.vertex_radius
            ),
            window(sf::VideoMode(settings.width, settings.height),
                   settings.title) {
        if (!font.loadFromFile("fonts/Times New Roman.ttf")) {
            throw std::runtime_error("Can't find font for text");
        }
    }


    void SFMLDrawing::AddCircle(const uint32_t &vertex_id) {
        auto [x, y] = point_ctx.GetCoords();

        sf::CircleShape shape(settings.vertex_radius);
        shape.setPosition(x, y);
        shape.setFillColor(settings.vertex_color);
        shape.setOutlineThickness(settings.border_width);
        shape.setOutlineColor(settings.outline_color);

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(vertex_id));
        text.setCharacterSize(settings.char_size);
        text.setFillColor(settings.text_color);
        const auto &[center_x, center_y] = CalcCenter(shape.getGlobalBounds());
        text.setPosition(center_x - settings.char_size / 2,
                         center_y - settings.char_size / 2);
        vertexes.insert({vertex_id, {vertex_id, shape, text}});

    }

    void SFMLDrawing::AddLine(uint32_t u, uint32_t v) {
        edges.emplace_back(u, v);
    }

    void SFMLDrawing::Draw() {
        std::vector<sf::RectangleShape> lines;

        for (const auto &it: edges) {
            const auto &u = vertexes[it.first];
            const auto &v = vertexes[it.second];
            const auto &[u_x, u_y] = CalcCenter(u.vertex.getGlobalBounds());
            const auto &[v_x, v_y] = CalcCenter(v.vertex.getGlobalBounds());

            sf::RectangleShape line(
            sf::Vector2f(GetDistance(u_x, u_y, v_x, v_y), 8));
            line.setFillColor(sf::Color::Black);
            if (u_x < v_x) {
                line.setPosition(u_x, u_y);
                line.setRotation(GetAngle(u_x, u_y, v_x, v_y));
            } else {
                line.setPosition(v_x, v_y);
                line.setRotation(GetAngle(v_x, v_y, u_x, u_y));
            }
            lines.push_back(line);
        }

        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear(sf::Color::White);
            for (const auto &line: lines) {
                window.draw(line);
            }
            for (const auto &[_, vertex]: vertexes) {
                window.draw(vertex.vertex);
                window.draw(vertex.text);
            }

            window.display();
        }

    }

}
