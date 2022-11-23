#pragma once

#include "../AbstractDrawing.hpp"

#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace drawing::impl {
    struct SFMLDrawSettings : public DrawSettings {
        float vertex_radius;
        sf::Color vertex_color;
        sf::Color outline_color;
        uint32_t border_width;
        uint32_t char_size;
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
        std::pair<float, float> NextCoord();

        struct PointCtx {
            PointCtx(float initial_x, float initial_y, double rotation);

            float x, y;
            double sin_phi, cos_phi;
        };

        SFMLDrawSettings settings;
        sf::RenderWindow window;
        std::unordered_map<uint32_t, SFMLVertexDescriptor> vertexes;
        std::vector<std::pair<uint32_t, uint32_t>> edges;
        PointCtx point_ctx;
        sf::Font font;
    };
}
