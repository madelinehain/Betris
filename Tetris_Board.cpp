// Copyright 2021 Madeline Clare Hain maddiech@bu.edu

#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
using std::cout;

int main() {
    sf::RenderWindow window(sf::VideoMode(720, 800), "maddiech@bu.edu");
    sf::Texture t, titleLoad, nextLoad, scoreLoad;

    t.loadFromFile("THISbackground.png");
    titleLoad.loadFromFile("title.png");
    nextLoad.loadFromFile("next.png");
    scoreLoad.loadFromFile("score.png");
    
    if(!t.loadFromFile("THISbackground.png")) return -1

    if(!titleLoad.loadFromFile("title.png")) return -1;
    if(!nextLoad.loadFromFile("next.png")) return -1;
    if(!scoreLoad.loadFromFile("score.png")) return -1;

    sf::Sprite background(t);
    sf::Sprite title(titleLoad);
    sf::Sprite next(nextLoad);
    sf::Sprite score(scoreLoad);
    
    window.setFramerateLimit(20);
    
    while (window.isOpen()) {
        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        background.setPosition(0,0);
        title.setPosition(420,20);
        next.setPosition(440,220);
        score.setPosition(420,460);
        window.draw(background);
        window.draw(title);
        window.draw(next);
        window.draw(score);
        window.display();
    }
    return 0;
}