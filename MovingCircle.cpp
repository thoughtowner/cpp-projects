#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), L"Иллюзия", sf::Style::Default);

    window.setVerticalSyncEnabled(true);

    sf::CircleShape circle(60);
    circle.setFillColor(sf::Color::White);
    circle.setOutlineThickness(5);
    circle.setOutlineColor(sf::Color::Red);

    bool goBack = false;
    float speed = 1.;
    int dir = 1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Up: speed += 0.2;
                    break;
                case sf::Keyboard::Down:
                    speed = std::max(0.0, speed - 0.2);
                    break;
                }
            }
        }
        
        // circle.setPosition(sf::Vector2f(circle.getPosition().x + 1, circle.getPosition().y));
        // circle.setPosition(circle.getPosition().x + 1, circle.getPosition().y);

        if (goBack == false) {
            circle.setPosition(sf::Vector2f(circle.getPosition().x + dir*speed, circle.getPosition().y));
            if (circle.getPosition().x > 600 - 120) {
                goBack = true;
            }
        }
        else {
            circle.setPosition(sf::Vector2f(circle.getPosition().x - dir*speed, circle.getPosition().y));
            if (circle.getPosition().x < 0) {
                goBack = false;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }
    return 0;
}
