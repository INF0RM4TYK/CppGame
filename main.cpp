#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Background.h"
#include "Menu.h"
#include "Game.h"
#include "Options.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

enum class State {
    MENU,
    RUNNING,
    OPTIONS,
    EXIT
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Formula-Typer");
    window.setFramerateLimit(60);
    Background background("background1.gif", window);

    // Ustawienie ikony
    sf::Image icon;
    icon.loadFromFile("assets/Icons/LogoMiniature.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Animacja tła
    std::vector<sf::Texture> frames;
    for (int i = 0; i < 179; ++i) {
        sf::Texture texture;
        std::string filename = "assets/frames/" + std::to_string(i) + ".gif";
        if (texture.loadFromFile(filename)) {
            frames.push_back(texture);
        }
    }

    sf::Sprite sprite;
    int currentFrame = 0;
    sf::Clock clock;
    sf::Time frameTime = sf::seconds(0.03f);

    State appState = State::MENU;
    Menu menu(WINDOW_WIDTH, WINDOW_HEIGHT);
    Game game(window);
    Options options(WINDOW_WIDTH, WINDOW_HEIGHT);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            switch (appState) {
                case State::MENU:
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2i mouse = sf::Mouse::getPosition(window);
                            if (menu.startB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                appState = State::RUNNING;
                            } else if (menu.optionsB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                appState = State::OPTIONS;
                            } else if (menu.exitB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                appState = State::EXIT;
                                window.close();
                            }
                        }
                    }
                    break;

                case State::OPTIONS:
                    options.moveUp();
                    options.moveDown();
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2i mouse = sf::Mouse::getPosition(window);
                            if (options.easyB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                game.setDifficulty(Game::Difficulty::EASY);
                            } else if (options.normalB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                game.setDifficulty(Game::Difficulty::NORMAL);
                            } else if (options.hardB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                game.setDifficulty(Game::Difficulty::HARD);
                            } else if (options.backB.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse))) {
                                appState = State::MENU;
                            }
                        }
                    }
                    break;

                case State::RUNNING:
                    game.run();
                    if (game.getState() == Game::State::MENU) {
                        appState = State::MENU;
                    }
                    break;

                default:
                    break;
            }
        }

        if (clock.getElapsedTime() >= frameTime) {
            currentFrame = (currentFrame + 1) % frames.size();
            sprite.setTexture(frames[currentFrame]);
            clock.restart();
        }

        window.clear();
        background.draw(window);

        if (appState == State::MENU) {
            window.draw(sprite);
            menu.draw(window);
        } else if (appState == State::OPTIONS) {
            options.draw(window);
        }

        window.display();
    }
}
