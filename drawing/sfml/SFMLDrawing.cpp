#include "SFMLDrawing.hpp"

namespace drawing::impl {


    SFMLDrawing::SFMLDrawing(uint32_t height, uint32_t width, const std::string &title) : height(height), width(width),
                                                                                          window(sf::VideoMode(width,
                                                                                                               height),
                                                                                                 title) {

    }


    void SFMLDrawing::DrawCircle() {

    }

    void SFMLDrawing::DrawLine() {

    }

    void SFMLDrawing::Draw() {
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);
        while (window.isOpen())
        {
            sf::Event event{};
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
        }

    }

}