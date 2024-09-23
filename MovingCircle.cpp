#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 600), L"MovingCircle", sf::Style::Default);

    sf::Texture sticker;
    if (!sticker.loadFromFile("sticker.png")) {
        std::cout << "Error loading texture...";
    }

    window.setVerticalSyncEnabled(true);

    sf::RectangleShape rect(sf::Vector2f(40, 40));
    rect.setTexture(&sticker);
    rect.setOrigin(20, 0);
    rect.setScale(5, 5);

    sf::Vector2u size = window.getSize();
    int width = size.x;
    int height = size.y;

    sf::Vector2f currentPosition;
    float differenceX = 0;
    float differenceY = 0;
    float rotationAngle = 0.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized) {
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                size = window.getSize();
                width = size.x;
                height = size.y;
            }
            if (event.type == sf::Event::MouseMoved) {
                currentPosition = rect.getPosition();
                differenceX = currentPosition.x - event.mouseMove.x;
                differenceY = currentPosition.y - event.mouseMove.y;
                if (sqrt(pow(differenceX, 2) + pow(differenceY, 2)) > 1) {
                    currentPosition.x = event.mouseMove.x;
                    currentPosition.y = event.mouseMove.y;
                    rotationAngle = atan2(differenceY, differenceX) / M_PI * 180 - 90;
                }
                rect.setPosition(sf::Vector2f(currentPosition.x, currentPosition.y));
                rect.setRotation(rotationAngle);
            }
        }
        window.clear();
        window.draw(rect);
        window.display();
    }
    return 0;
}