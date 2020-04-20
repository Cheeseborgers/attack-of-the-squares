//
//      Created by Goodecheeseburgers on 19/04/2020.
//      SomeRPG. A C++ console role playing game.
//      Copyright (C) 2020 - goodecheeseburgers@gmail.com
//
//      https://github.com/Cheeseborgers/SomeRPG
//
//      This program is free software: you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation, either version 3 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H

#include <iostream>
#include <memory>
#include <vector>
#include <ctime>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

/*
 * Wrapper class that acts as the game engine
 * */

class Game {

private:
    std::unique_ptr<sf::RenderWindow> window;
    sf::VideoMode videoMode;
    sf::Event ev{};

    // Mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    // Game logic
    bool endGame{};
    unsigned points{};
    int health{};
    float enemySpawnTimer{};
    float enemySpawnTimerMax{};
    int maxEnemies{};
    bool mouseHeld{};

    // Game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    // Private methods
    void initVariables();
    void initWindow();
    void initEnemies();

public:
    // Constructors
    Game();

    // Accessors
    [[nodiscard]] inline bool isRunning() const {return  window->isOpen(); };
    inline bool getEndGame() const { return this->endGame; };

    // Methods
    void spawnEnemy();
    void pollEvents();
    void updateMousePos();
    void updateEnemies();
    void update();
    void renderEnemies();
    void render();

};

#endif //UNTITLED_GAME_H
