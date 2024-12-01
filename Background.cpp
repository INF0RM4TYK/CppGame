#include "Background.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include <iostream>

Background::Background(const std::string& filePath, sf::RenderWindow& window) {
    texture.loadFromFile("background1.gif");
    sprite.setTexture(texture);
}


void Background::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}



