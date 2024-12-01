// options.cpp

#include "options.h"
#include <iostream>

Options::Options(float width, float height) : selectedIndex(0) {
    if (!font.loadFromFile("assets/fonts/Roboto-Italic.ttf")) {
        std::cerr << "Nie można załadować czcionki!" << std::endl;
    }

    title.setFont(font);
    title.setFillColor(sf::Color::White);
    title.setString("Difficulty Options");
    title.setCharacterSize(40);
    title.setPosition(width / 2 - title.getGlobalBounds().width / 2, height / 8);

    positionButtons(width, height);
}

void Options::positionButtons(float width, float height) {
    float buttonWidth = 200;
    float xPos = width / 2 - buttonWidth / 2;
    float yPos = height / 2 - 50;

    setButtonStyle(easyB, easyBT, "Easy", xPos, yPos - 80);
    setButtonStyle(normalB, normalBT, "Normal", xPos, yPos);
    setButtonStyle(hardB, hardBT, "Hard", xPos, yPos + 80);
    setButtonStyle(backB, backBT, "Back to Menu", xPos, yPos + 160);
}

void Options::setButtonStyle(sf::RectangleShape& button, sf::Text& buttonText, const std::string& text, float xPos, float yPos) {
    float buttonWidth = 200;
    float buttonHeight = 60;

    button.setSize(sf::Vector2f(buttonWidth, buttonHeight));
    button.setFillColor(sf::Color(70, 130, 180, 150));  // Steel Blue z przezroczystością
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(2);
    button.setPosition(sf::Vector2f(xPos, yPos));

    buttonText.setFont(font);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setString(text);
    buttonText.setCharacterSize(24);
    buttonText.setPosition(xPos + (buttonWidth - buttonText.getGlobalBounds().width) / 2, yPos + (buttonHeight - buttonText.getGlobalBounds().height) / 2 - 10);
}

void Options::draw(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(easyB);
    window.draw(normalB);
    window.draw(hardB);
    window.draw(backB);
    window.draw(easyBT);
    window.draw(normalBT);
    window.draw(hardBT);
    window.draw(backBT);
}

void Options::moveUp() {
    if (selectedIndex > 0) {
        selectedIndex--;
    }
}

void Options::moveDown() {
    if (selectedIndex < 3) {
        selectedIndex++;
    }
}

int Options::getSelectedIndex() const {
    return selectedIndex;
}

bool Options::isBackSelected() const {
    return selectedIndex == 3;
}
