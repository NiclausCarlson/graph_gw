#pragma once

#include "../AbstractDrawing.hpp"

#include <SFML/Graphics.hpp>


namespace drawing::impl {
    struct SFMLDrawSettings : public DrawSettings {

    };

    class SFMLDrawing : public AbstractDrawing {
    public:
        explicit SFMLDrawing(const SFMLDrawSettings &settings);

        void DrawCircle() override;

        void DrawLine() override;

        void Draw() override;

    private:
        sf::RenderWindow window;
    };
}
