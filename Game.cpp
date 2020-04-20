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

#include "Game.h"

// Private methods -----------------------------------------------------------------------------------------------------
void Game::initVariables()
{
    this->window = nullptr;

    this->endGame = false;
    this->points = 0;
    this->health = 20;
    this->enemySpawnTimerMax = 20.F;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
}
//----------------------------------------------------------------------------------------------------------------------
void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = std::make_unique<sf::RenderWindow>(this->videoMode, "Window", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::initEnemies()
{
    this->enemy.setPosition(sf::Vector2f(0.F, 0.F));
    this->enemy.setSize(sf::Vector2f(100.F, 100.F));
    this->enemy.setFillColor(sf::Color::Cyan);
}
// Constructor ---------------------------------------------------------------------------------------------------------
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initEnemies();
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::updateMousePos()
{
    /*
     * @ return void
     *   Updates the mouses positions:
     * - Mouse position relative to window (Vector2i)
     * */

    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::updateEnemies()
{
    /* @ return void
     * Updates the enemy spawn timer and spawns enemies
     * when the total amount of enemies is smaller than the max amount
     * Moves the enemies downwards
     * Removes the enemies at the edge of the screen //TODO
     * */

    // Updating the timer for the enemy spawning
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            // Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.F;
        }
        else {
            // Increment timer
            this->enemySpawnTimer += 1.F;
        }
    }

    // Moving and updating the enemies
    for (size_t i = 0; i < this->enemies.size(); ++i)
    {
        bool deleted{false};

        this->enemies[i].move(0.F, 5.F);

        // Check enemy hasnt left the screen
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            deleted = true;
            this->enemies.erase(this->enemies.begin() + i);

            // Lose health
            this->health -= 1;
        }
    }

    // Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!this->mouseHeld) {

            this->mouseHeld = true;

            bool deleted{false};

            for (size_t i = 0; i < this->enemies.size() && !deleted; ++i) {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                    // Delete enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);

                    // Gain points
                    this->points += 1;
                }
            }
        }
    }
    else {
        this->mouseHeld = false;
    }
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::update()
{
    this->pollEvents();

    if (!this->endGame)
    {
        this->updateMousePos(); // Update mouse position

        this->updateEnemies(); // Update enemies
    }

    // End game condition
    if (this->health <= 0)
    {
        this->endGame = true;
    }
}
//----------------------------------------------------------------------------------------------------------------------
void Game::renderEnemies()
{
    for (auto &e : this->enemies)
    {
        this->window->draw(e);
    }
}
// ---------------------------------------------------------------------------------------------------------------------
void Game::render()
{
    /*
     * @return void
     *  Renders the game objects
     * -clear old frame
     * - renders objects
     * - display frame in window
     * -*/

    this->window->clear(); // Use default black clear value

    // Draw game objects
    this->renderEnemies();

    // Display frame in window
    this->window->display();
}
// -------------------------------------------------------------------------------------------
void Game::pollEvents()
{
    // Event polling
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed: {
                this->window->close();
                break;
            }
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
            default: {
                break;
            }
        }
    }
}
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"
//----------------------------------------------------------------------------------------------------------------------
void Game::spawnEnemy()
{
    /* @return void
     * Spawns enemies and sets their position and colour
     * -Sets a random position
     * -Sets a random colour
     * -Adds enemy to the enemies vector
     * */


    // Set the enemy position
    this->enemy.setPosition(
            static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
            0.F
    );

    // Set fill colour
    this->enemy.setFillColor(sf::Color::Green);

    // Spawn enemy
    this->enemies.emplace_back(this->enemy);

}
#pragma clang diagnostic pop

