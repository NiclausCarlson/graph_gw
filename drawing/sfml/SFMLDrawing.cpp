#include "SFMLDrawing.hpp"

namespace drawing::impl {

    SFMLDrawing::SFMLDrawing(const SFMLDrawSettings &settings) :
            window(sf::VideoMode(settings.width,
                                 settings.height),
                   settings.title) {

    }


    void SFMLDrawing::DrawCircle() {

    }

    void SFMLDrawing::DrawLine() {

    }

    void SFMLDrawing::Draw() {
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);
        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
        }

    }

}
