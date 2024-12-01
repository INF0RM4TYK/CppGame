#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream> // std::ifstream

class Game {
public:
    enum class State {
        MENU,
        RUNNING,
        OPTIONS,
        EXIT
    };

    enum class Difficulty {
        EASY,
        NORMAL,
        HARD
    };

    Game(sf::RenderWindow& window);

    void run();
    void setDifficulty(Difficulty difficulty);
    State getState() const;

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text userInput;

    State gameState;
    Difficulty currentDifficulty;

    std::vector<std::string> wordsToType;
    std::vector<sf::Text> flyingWords;
    int score;
    sf::Time spawnTime;
    int maxWords;

    float wordSpeed;  // Prędkość ruchu słów




    void setupText();
    void handleInput(sf::Event& event);
    void update();
    void render();
    void spawnFlyingWord();
    void updateWordSpeed();  // Nowa metoda do aktualizacji prędkości słów
};

#endif
