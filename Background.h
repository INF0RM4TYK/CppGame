#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>

class Background {
public:

    Background(const std::string& filePath, sf::RenderWindow& window);
    void update();
    void draw(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Color backgroundColor;
};

#endif