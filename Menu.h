#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
public:
    Menu(float width, float height);

    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;
    bool isSelected() const;

    sf::RectangleShape startB;
    sf::RectangleShape optionsB;
    sf::RectangleShape exitB;

private:
    int selectedIndex;
    sf::Font font;
    sf::Text logo;
    std::vector<sf::Text> menuItems;

    sf::Text startBT;
    sf::Text optionsBT;
    sf::Text exitBT;

    void positionButtons(float width, float height);
    void setButtonStyle(sf::RectangleShape& button, sf::Text& buttonText, const std::string& text, float xPos, float  yPos);
};

#endif
