#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <cmath>

int main()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(desktopMode.width, desktopMode.height), L"MovingCircle", sf::Style::Fullscreen);

    sf::Vector2u size = window.getSize();
    int width = size.x;
    int height = size.y;

    window.setVerticalSyncEnabled(true);

    sf::CircleShape mouseCircle(80);
    mouseCircle.setFillColor(sf::Color::White);
    mouseCircle.setPosition(width, height);
    mouseCircle.setOrigin(mouseCircle.getRadius(), mouseCircle.getRadius());

    sf::CircleShape randomCircle(80);
    randomCircle.setFillColor(sf::Color::Red);
    randomCircle.setPosition(randomCircle.getRadius(), randomCircle.getRadius());
    randomCircle.setOrigin(randomCircle.getRadius(), randomCircle.getRadius());

    // bool isMinRadius = true;

    int eventMouseMoveY = 0;
    int eventMouseMoveX = 0;

    std::srand(std::time(nullptr));
    float randomCircleSpeed = 16;
    float randomCirclePositionX = rand() % (width - 2 * (int)randomCircle.getRadius()) + (int)randomCircle.getRadius();
    float randomCirclePositionY = rand() % (height - 2 * (int)randomCircle.getRadius()) + (int)randomCircle.getRadius();
    float deltaRandomCirclePositionX = randomCirclePositionX - randomCircle.getPosition().x;
    float deltaRandomCirclePositionY = randomCirclePositionY - randomCircle.getPosition().y;
    float movementAngle = atan2(deltaRandomCirclePositionY, deltaRandomCirclePositionX) + M_PI/2;

    std::list<sf::Vector2f> mouseCirclePositions;
    sf::Vector2f currentMouseCirclePosition = mouseCircle.getPosition();
    float currentMouseCirclePositionX = currentMouseCirclePosition.x;
    float currentMouseCirclePositionY = currentMouseCirclePosition.y;

    int randomCircleBouncesNumber = 0;
    sf::CircleShape bonus(40);
    float bonusPositionX = rand() % (width - 2 * (int)bonus.getRadius()) + (int)bonus.getRadius();
    float bonusPositionY = rand() % (height - 2 * (int)bonus.getRadius()) + (int)bonus.getRadius();
    bonus.setFillColor(sf::Color::Yellow);
    bonus.setPosition(bonusPositionX, bonusPositionY);
    bonus.setOrigin(bonus.getRadius(), bonus.getRadius());
    bool isBonusExist = false;

    bool isMouseCircleDelayValueExists = false;
    int mouseCircleDelayValue = 4;

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
                eventMouseMoveX = event.mouseMove.x;
                eventMouseMoveY = event.mouseMove.y;
            }
        }





        if (abs(randomCircle.getPosition().x - randomCirclePositionX) <= randomCircleSpeed && abs(randomCircle.getPosition().y - randomCirclePositionY) <= randomCircleSpeed) {
            randomCirclePositionX = rand() % (width - 2 * (int)randomCircle.getRadius()) + (int)randomCircle.getRadius();
            randomCirclePositionY = rand() % (height - 2 * (int)randomCircle.getRadius()) + (int)randomCircle.getRadius();

            deltaRandomCirclePositionX = randomCirclePositionX - randomCircle.getPosition().x;
            deltaRandomCirclePositionY = randomCirclePositionY - randomCircle.getPosition().y;

            movementAngle = atan2(deltaRandomCirclePositionY, deltaRandomCirclePositionX) + M_PI / 2;

            mouseCircle.setRadius(mouseCircle.getRadius() + 5);
            mouseCircle.setOrigin(mouseCircle.getRadius(), mouseCircle.getRadius());

            randomCircleBouncesNumber += 1;
        }
        else {
            randomCircle.setPosition(randomCircle.getPosition().x + sin(movementAngle) * randomCircleSpeed, randomCircle.getPosition().y - cos(movementAngle) * randomCircleSpeed);
        }





        if (randomCircleBouncesNumber >= 5 && !isBonusExist) {
            isBonusExist = true;
            bonusPositionX = rand() % (width - 2 * (int)bonus.getRadius()) + (int)bonus.getRadius();
            bonusPositionY = rand() % (height - 2 * (int)bonus.getRadius()) + (int)bonus.getRadius();

            bonus.setPosition(bonusPositionX, bonusPositionY);
        }





        // Постоянно увеличиваем и уменьшаем радиус mouseCircle

        /*if (isMinRadius) {
            mouseCircle.setRadius(mouseCircle.getRadius() + 1);
            if (mouseCircle.getRadius() >= 120) {
                isMinRadius = false;
            }
        }
        else {
            mouseCircle.setRadius(mouseCircle.getRadius() - 1);
            if (mouseCircle.getRadius() <= 80) {
                isMinRadius = true;
            }
        }*/

        if (isMouseCircleDelayValueExists) {
            if (mouseCirclePositions.size() <= mouseCircleDelayValue) {
                mouseCirclePositions.emplace_back(sf::Vector2f(eventMouseMoveX, eventMouseMoveY));
            }
            else {
                currentMouseCirclePosition = mouseCirclePositions.front();
                mouseCirclePositions.pop_front();
            }

            currentMouseCirclePositionX = currentMouseCirclePosition.x;
            currentMouseCirclePositionY = currentMouseCirclePosition.y;
        }
        else {
            currentMouseCirclePositionX = eventMouseMoveX;
            currentMouseCirclePositionY = eventMouseMoveY;
        }

        if (currentMouseCirclePositionY < mouseCircle.getRadius() && !(currentMouseCirclePositionX < mouseCircle.getRadius())) {
            if (currentMouseCirclePositionX > width - mouseCircle.getRadius()) {
                mouseCircle.setPosition(sf::Vector2f(width - mouseCircle.getRadius(), mouseCircle.getRadius()));
            }
            else {
                mouseCircle.setPosition(sf::Vector2f(currentMouseCirclePositionX, mouseCircle.getRadius()));
            }
        }
        else if (currentMouseCirclePositionX > width - mouseCircle.getRadius()) {
            if (currentMouseCirclePositionY > height - mouseCircle.getRadius()) {
                mouseCircle.setPosition(sf::Vector2f(width - mouseCircle.getRadius(), height - mouseCircle.getRadius()));
            }
            else {
                mouseCircle.setPosition(sf::Vector2f(width - mouseCircle.getRadius(), currentMouseCirclePositionY));
            }
        }
        else if (currentMouseCirclePositionY > height - mouseCircle.getRadius()) {
            if (currentMouseCirclePositionX < mouseCircle.getRadius()) {
                mouseCircle.setPosition(sf::Vector2f(mouseCircle.getRadius(), height - mouseCircle.getRadius()));
            }
            else {
                mouseCircle.setPosition(sf::Vector2f(currentMouseCirclePositionX, height - mouseCircle.getRadius()));
            }
        }
        else if (currentMouseCirclePositionX < mouseCircle.getRadius()) {
            if (currentMouseCirclePositionY < mouseCircle.getRadius()) {
                mouseCircle.setPosition(sf::Vector2f(mouseCircle.getRadius(), mouseCircle.getRadius()));
            }
            else {
                mouseCircle.setPosition(sf::Vector2f(mouseCircle.getRadius(), currentMouseCirclePositionY));
            }
        }
        else {
            mouseCircle.setPosition(sf::Vector2f(currentMouseCirclePositionX, currentMouseCirclePositionY));
        }





        if (sqrt(pow(mouseCircle.getPosition().x - randomCircle.getPosition().x, 2) + pow(mouseCircle.getPosition().y - randomCircle.getPosition().y, 2)) <= mouseCircle.getRadius() + randomCircle.getRadius()) {
            break;
        }





        if (isBonusExist) {
            if (sqrt(pow(mouseCircle.getPosition().x - bonus.getPosition().x, 2) + pow(mouseCircle.getPosition().y - bonus.getPosition().y, 2)) <= mouseCircle.getRadius() + bonus.getRadius()) {
                window.clear(sf::Color::Black);
                window.draw(mouseCircle);
                window.draw(randomCircle);
                window.display();
                if (mouseCircle.getRadius() - 40 >= 60) {
                    mouseCircle.setRadius(mouseCircle.getRadius() - 40);
                }
                else {
                    mouseCircle.setRadius(60);
                }
                mouseCircle.setOrigin(mouseCircle.getRadius(), mouseCircle.getRadius());
                isBonusExist = false;
                randomCircleBouncesNumber = 0;
            }
            else if (sqrt(pow(randomCircle.getPosition().x - bonus.getPosition().x, 2) + pow(randomCircle.getPosition().y - bonus.getPosition().y, 2)) <= randomCircle.getRadius() + bonus.getRadius()) {
                window.clear(sf::Color::Black);
                window.draw(mouseCircle);
                window.draw(randomCircle);
                window.display();
                randomCircleSpeed += 8;
                isBonusExist = false;
                randomCircleBouncesNumber = 0;
            }
        }





        window.clear(sf::Color::Black);
        if (isBonusExist) {
            window.draw(bonus);
        }
        window.draw(mouseCircle);
        window.draw(randomCircle);
        window.display();

    }
    return 0;
}