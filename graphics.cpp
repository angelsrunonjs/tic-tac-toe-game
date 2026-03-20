#include <SFML/Graphics.hpp>
#include<iostream>
#include <string>
#include "Gamelogic.h"

int getCell(sf::Vector2i p) {
    //1st row
    if (p.x < 200 && p.y < 200) return 0;
    else if (p.x < 400 && p.y < 200) return 1;
    else if (p.x < 600 && p.y < 200) return 2;
    //2nd row
    else if (p.x < 200 && p.y < 400) return 3;
    else if (p.x < 400 && p.y < 400) return 4;
    else if (p.x < 600 && p.y < 400) return 5;
    //3rd row
    else if (p.x < 200 && p.y < 600) return 6;
    else if (p.x < 400 && p.y < 600) return 7;
    else if (p.x < 600 && p.y < 600) return 8;
    return -1;
}

sf::RectangleShape defineX(int rotation) {
    float size = 150.f;
    float thickness = 3.f;
    sf::RectangleShape diagonal({ size, thickness });
    
    diagonal.setFillColor(sf::Color::Red);
  
    diagonal.setOrigin({ size / 2, thickness / 2 });

    diagonal.setRotation(sf::degrees(rotation));
    
    return diagonal;
}

sf::CircleShape defineO(sf::Vector2f center) {
    float thickness = 3.f;
    sf::CircleShape o(60.f);
    o.setFillColor(sf::Color::Black);
    o.setOutlineThickness(thickness);
    o.setOutlineColor(sf::Color::Blue);
    o.setOrigin({ o.getRadius(), o.getRadius() });
    o.setPosition(center);

    return o;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 600, 600 }), "Test Window");

    //board
    sf::RectangleShape rectangle1({ 3.f, 500.f });
    sf::RectangleShape rectangle2({ 3.f, 500.f });
    sf::RectangleShape rectangle3({ 500.f, 3.f });
    sf::RectangleShape rectangle4({ 500.f, 3.f });

    sf::Vector2f cell[9] = {
    {100,100}, {300,100}, {500,100},
    {100,300}, {300,300}, {500,300},
    {100,500}, {300,500}, {500,500}
    }; //cell centers

    //vertical
    rectangle1.setPosition({ 200.f, 50.f });
    rectangle2.setFillColor(sf::Color::White);
    rectangle2.setPosition({ 400.f, 50.f });

    //horizontal
    rectangle3.setFillColor(sf::Color::White);
    rectangle4.setFillColor(sf::Color::White);
    rectangle3.setPosition({ 50.f, 200.f });
    rectangle4.setPosition({ 50.f, 400.f });

    sf::RectangleShape x1, x2;
    sf::CircleShape o;

    sf::Font font;
    if (!font.openFromFile("capacitor.ttf")) {
        std::cout << "couldn't load font" << std::endl;
    }

    sf::Text message(font);
    message.setCharacterSize(50.f);
    message.setFillColor(sf::Color::Green);
    message.setPosition({ 190.f, 200.f });

    int turn = 0;
    int check = -1;
    int winStatus = -1;

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {

                // if game already ended, next click resets
                if (winStatus != -1) {
                    resetGame();
                    turn = 0;
                    check = -1;
                    winStatus = -1;
                    message.setString("");
                    continue;
                }

                // otherwise allow move
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                int c = getCell(pos);
                if (c == -1) continue;

                if (space[c] != 'X' && space[c] != 'O') {
                    playermove(turn, c);
                    turn++;

                    check = checkgamestatus();

                    if (check == 0 || check == 1) {
                        winStatus = check;
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(rectangle1);
        window.draw(rectangle2);
        window.draw(rectangle3);
        window.draw(rectangle4);

        for (int i = 0; i < 9; i++) {
            if (space[i] == 'X') {
                x1 = defineX(45);
                x2 = defineX(-45);
                x1.setPosition(cell[i]);
                x2.setPosition(cell[i]);
                window.draw(x1);
                window.draw(x2);
            }
            else if (space[i] == 'O') {
                o = defineO(cell[i]);
                window.draw(o);
            }
        }

        if (winStatus == 1) {
            if (turn % 2 == 0) {
                message.setString("O wins");
            }
            else {
                message.setString("X wins");
            }
        }
        else if (winStatus == 0) {
            message.setString("Draw");
        }
        else {
            message.setString("");
        }

        window.draw(message);
        window.display();
    }

        window.clear(sf::Color::Black);
        window.draw(rectangle1);
        window.draw(rectangle2);
        window.draw(rectangle3);
        window.draw(rectangle4);

        for (int i = 0; i < 9; i++) {
            if (space[i] == 'X') {
                
                x1 = defineX(45);
                x2 = defineX(-45);
                x1.setPosition(cell[i]);
                x2.setPosition(cell[i]);
                window.draw(x1);
                window.draw(x2);
            }
            else if (space[i] == 'O') {
                
                o = defineO(cell[i]);
                window.draw(o);
            }
        }
        if (check == 1) {
            if (turn % 2 == 0) {
                message.setString("O wins");
            }
            else {
                message.setString("X wins");
            }
        }
        else if (check == 0) {
            message.setString("Draw");
        }
        window.draw(message);
        window.display();
}