#pragma once

#include "../AbstractDrawing.hpp"

#include <SFML/Graphics.hpp>


namespace drawing::impl {
    class SFMLDrawing : public AbstractDrawing {
    public:
        explicit SFMLDrawing(uint32_t height = 800, uint32_t width = 600, const std::string &title = "Graph");

        void DrawCircle() override;

        void DrawLine() override;

        void Draw() override;

    private:
        sf::RenderWindow window;

        uint32_t height, width;

    };
}
