// options.h

#ifndef OPTIONS_H
#define OPTIONS_H

#include <SFML/Graphics.hpp>
#include <vector>

class Options {
public:
    Options(float width, float height);

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;
    bool isBackSelected() const;

    sf::RectangleShape easyB;
    sf::RectangleShape normalB;
    sf::RectangleShape hardB;
    sf::RectangleShape backB;

private:
    int selectedIndex;
    sf::Font font;
    sf::Text title;
    sf::Text easyBT;
    sf::Text normalBT;
    sf::Text hardBT;
    sf::Text backBT;

    void positionButtons(float width, float height);
    void setButtonStyle(sf::RectangleShape& button, sf::Text& buttonText, const std::string& text, float xPos, float yPos);
};

#endif // OPTIONS_H
