#pragma once

#include "../AbstractDrawing.hpp"

#include <SFML/Graphics.hpp>
#include <unordered_map>

namespace drawing::impl {
    struct SFMLDrawSettings : public DrawSettings {
        sf::Color vertex_color;
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
        std::unordered_map<uint32_t, VertexDescriptor> vertexes;
    };
}
