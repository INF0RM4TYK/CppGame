#include "game.h"
#include <iostream>
#include <cstdlib> // rand(), srand()
#include <ctime>   // time()

Game::Game(sf::RenderWindow& window) : window(window), score(0), gameState(State::MENU), currentDifficulty(Difficulty::NORMAL), wordSpeed(1.5f) {
    if (!font.loadFromFile("assets/fonts/Roboto-Italic.ttf")) {
        std::cerr << "Nie udało się załadować czcionki!" << std::endl;
    }

    setupText(); // Ustawienie początkowego tekstu do wpisania
    srand(static_cast<unsigned>(time(nullptr))); // Inicjalizacja generatora liczb pseudolosowych
}




void Game::run() {
    std::ifstream inputFile("assets/f1words.txt"); // Plik z listą słów do wpisania
    if (!inputFile.is_open()) {
        std::cerr << "Nie udało się otworzyć pliku f1words.txt!" << std::endl;
        return;
    }

    std::string word;
    while (inputFile >> word) {
        wordsToType.push_back(word);
    }
    inputFile.close();

    sf::Clock clock;
    sf::Time spawnTime = sf::seconds(1.5f); // Czas między kolejnymi pojawieniami słów

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            handleInput(event);
        }

        if (clock.getElapsedTime() >= spawnTime) {
            spawnFlyingWord();
            clock.restart();
        }

        update();
        render();
    }
}

void Game::setupText() {
    userInput.setFont(font);
    userInput.setCharacterSize(24);
    userInput.setPosition(100.f, 500.f);
}

void Game::handleInput(sf::Event& event) {
    // Obsługa wejścia (np. klawiatura)
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode >= 32 && event.text.unicode <= 126) {
            char typedChar = static_cast<char>(event.text.unicode);
            userInput.setString(userInput.getString() + typedChar);
        }
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Backspace) {
            // Usunięcie ostatniego wpisanego znaku
            std::string currentText = userInput.getString().toAnsiString();
            if (!currentText.empty()) {
                currentText.pop_back();
                userInput.setString(currentText);
            }
        } else if (event.key.code == sf::Keyboard::Enter) {
            // Sprawdzenie, czy wpisane słowo znajduje się na liście lecących słów
            std::string typedWord = userInput.getString().toAnsiString();
            for (auto it = flyingWords.begin(); it != flyingWords.end(); ++it) {
                std::string flyingWord = it->getString().toAnsiString();
                if (typedWord == flyingWord) {
                    flyingWords.erase(it); // Usunięcie słowa z listy lecących
                    score++; // Dodanie punktu za poprawne wpisanie słowa
                    break; // Przerwanie pętli, bo słowo zostało znalezione
                }
            }
            // Wyczyść pole wpisywania po sprawdzeniu słowa
            userInput.setString("");
        }
    }
}

void Game::update() {
    // Aktualizacja lecących słów (przesunięcie ich, usunięcie tych, które wyleciały poza ekran)
    for (size_t i = 0; i < flyingWords.size(); ++i) {
        flyingWords[i].move(wordSpeed, 0.f); // Przesunięcie słowa w prawo (prędkość zależna od poziomu trudności)
        if (flyingWords[i].getPosition().x > window.getSize().x) {
            // Słowo wyleciało poza ekran, odejmowanie punktów
            flyingWords.erase(flyingWords.begin() + i);
            score--; // Odejmowanie punktów za słowo, które ominęło gracza
        }
    }
}

void Game::render() {
    window.clear(sf::Color(30, 30, 30));

    // Rysowanie wszystkich lecących słów
    for (const auto& word : flyingWords) {
        window.draw(word);
    }

    window.draw(userInput); // Rysowanie pola do wpisywania tekstu

    // Rysowanie punktów na ekranie
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Punkty: " + std::to_string(score));
    scoreText.setPosition(10.f, 10.f);
    window.draw(scoreText);

    window.display(); // Wyświetlenie wszystkich zmian na ekranie
}

void Game::spawnFlyingWord() {
    if (wordsToType.empty()) {
        return; // Jeśli skończyły się słowa do typowania, nie twórz nowych
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setString(wordsToType[rand() % wordsToType.size()]);
    text.setFillColor(sf::Color::White);
    text.setPosition(-100.f, static_cast<float>(rand() % (window.getSize().y - 100))); // Losowa wysokość

    flyingWords.push_back(text);
}

void Game::setDifficulty(Difficulty difficulty) {
    currentDifficulty = difficulty;
    updateWordSpeed();
}

Game::State Game::getState() const {
    return gameState;
}

void Game::updateWordSpeed() {
    switch (currentDifficulty) {
        case Difficulty::EASY:
            wordSpeed = 1.0f;
            spawnTime = sf::seconds(2.0f);
            break;
        case Difficulty::NORMAL:
            wordSpeed = 1.5f;
            spawnTime = sf::seconds(1.0f);
            break;
        case Difficulty::HARD:
            wordSpeed = 2.5f;
            spawnTime = sf::seconds(0.5f);
            break;
    }
}
