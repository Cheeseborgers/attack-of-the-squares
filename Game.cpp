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
    this->enemiesKilled = 0;
    this->playerHealth = 20;
    this->enemySpawnTimerMax = 20.F;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;
}

//----------------------------------------------------------------------------------------------------------------------
void Game::initWindow() {
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = std::make_unique<sf::RenderWindow>(this->videoMode, "Window",
                                                      sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

// ----------------------------------------------------------------------------------------------
void Game::initFonts() {
    if (!this->primaryFont.loadFromFile("fonts/chlorinar/CHLORINR.TTF")) {
        std::cout << "ERROR::GAME::INITFONTS PRIMARY FONT FAILED TO LOAD\n";
    }

    if (!this->secondaryFont.loadFromFile("fonts/hemi-head-426/hemi_head_bdit.ttf")) {
        std::cout << "ERROR::GAME::INITFONTS SECONDARY FONT FAILED TO LOAD\n";
    }
}

// --------------------------------------------------------------------------------------------------------------
void Game::initText() {
    this->uiText.setFont(this->secondaryFont);
    this->uiText.setCharacterSize(18);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

// ---------------------------------------------------------------------------------------------------------------------
void Game::initEnemies() {

}

// Constructor ---------------------------------------------------------------------------------------------------------
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
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
void Game::updateSpawnTimer() {
    // Updating the timer for the enemy spawning
    if (this->enemies.size() < this->maxEnemies) {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            // Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.F;
        } else {
            // Increment timer
            this->enemySpawnTimer += 1.F;
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------
void Game::updateClickedEnemies() {

    /* @ return void
     * Detects a left click event from the mouse, setting the enemy as 'dead' if the mouse
     *   pointer is within the its shape global bounds.
     * - Waits for left click
     * - Detects and toggles left mouse button held check
     * - If the mouse button is not held, sets the enemy as dead
     * - Increments player points
     * */

    // Check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (!this->mouseHeld) {

            this->mouseHeld = true;

            for (size_t i = 0; i < this->enemies.size(); ++i) {
                if (this->enemies[i]->getShape().getGlobalBounds().contains(this->mousePosView)) {
                    // Gain points
                    this->points += this->enemies[i]->getPointsGained();

                    // Increment kill counter
                    this->enemiesKilled += 1;

                    // Delete enemy
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        }
    } else {
        this->mouseHeld = false;
    }
}

// ---------------------------------------------------------------------------------------------------------------------
void Game::updateEnemies() {
    /* @ return void
     * - Moves the enemies downwards
     * - Removes the enemies at the edge of the screen
     * - Removes 1 point from the players health
     * */

    // Moving and updating the enemies
    for (size_t i = 0; i < this->enemies.size(); ++i) {
        // Move the enemy
        this->enemies[i]->update();

        // Check if enemy has left the screen
        if (this->enemies[i]->getShape().getPosition().y > this->window->getSize().y) {
            // Remove the enemy
            this->enemies.erase(this->enemies.begin() + i);

            // Player lose playerHealth
            this->playerHealth -= 1;
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------
void Game::updateText() {
    std::stringstream ss;

    ss << "Points: " << this->points << "\n"
       << "Health: " << this->playerHealth << "\n"
       << "E: " << this->enemies.size() << "\n"
       << "Kills: " << this->enemiesKilled << "\n";

    this->uiText.setString(ss.str());
}

// ---------------------------------------------------------------------------------------------------------------------
void Game::update() {
    /* @return void
     * Polls and updates game events and controls playerHealth end game condition
     * - Poll events
     * - Updates mouse position
     * - Updates enemies
     * - Ends game at zero playerHealth
     * */

    this->pollEvents();

    if (!this->endGame) {
        this->updateMousePos(); // Update mouse position

        this->updateClickedEnemies();

        this->updateText(); // Update text

        this->updateSpawnTimer(); // Update the enemy spawn timer

        this->updateEnemies(); // Update enemies
    }

    // End game condition
    if (this->playerHealth <= 0) {
        this->endGame = true;
    }
}

//----------------------------------------------------------------------------------------------------------------------
void Game::renderEnemies() {
    for (auto &e : this->enemies) {
        e->render(*this->window);
    }
}

// ---------------------------------------------------------------------------------------------------------------------
void Game::renderText(sf::RenderTarget &target) {
    target.draw(this->uiText);
}

// ---------------------------------------------------------------------------------------------------------------------
void Game::render() {
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

    // Draw text
    this->renderText(*this->window);

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
void Game::spawnEnemy() {
    /* @return void
     * Spawns enemies and sets their position and colour
     * -Sets a random position
     * -Sets a random colour
     * -Adds enemy to the enemies vector
     * */

    int enemyType = rand() % 5; // enemy type 1-4

    // Spawn enemy
    auto e = std::make_unique<Enemy>(*this->window, enemyType);
    this->enemies.push_back(std::move(e));
}


#pragma clang diagnostic pop

