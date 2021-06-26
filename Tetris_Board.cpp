// Copyright 2021 Madeline Clare Hain maddiech@bu.edu

#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
using std::cout;

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "maddiech@bu.edu");
    sf::Texture t;
    t.loadFromFile("background.png");
    
    if(!t.loadFromFile("background.png")) {
        return -1;
    }
    
    sf::Sprite background(t);
    
    window.setFramerateLimit(20);
    
    while (window.isOpen()) {
        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(background);
        window.display();
    }
    return 0;
}