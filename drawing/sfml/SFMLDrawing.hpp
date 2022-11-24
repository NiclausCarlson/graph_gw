#pragma once

#include "../AbstractDrawing.hpp"

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "../vertex_coord_generator/CoordGenerator.hpp"


namespace drawing::impl {
    struct SFMLDrawSettings : public DrawSettings {
        sf::Color vertex_color;
        sf::Color outline_color;
        uint32_t border_width;
        sf::Color text_color;
    };

    struct SFMLVertexDescriptor : public VertexDescriptor {
        sf::CircleShape vertex;
        sf::Text text;
    };

    class SFMLDrawing : public AbstractDrawing {
    public:
        explicit SFMLDrawing(const SFMLDrawSettings &settings);

        void AddCircle(const uint32_t &vertex_id) override;

        void AddLine(uint32_t u, uint32_t v) override;

        void Draw() override;

    private:
        SFMLDrawSettings settings;
        sf::RenderWindow window;
        std::unordered_map<uint32_t, SFMLVertexDescriptor> vertexes;
        std::vector<std::pair<uint32_t, uint32_t>> edges;
        coords::CoordGenerator point_ctx;
        sf::Font font;
    };
}
