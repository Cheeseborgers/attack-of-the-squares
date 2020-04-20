//
//      Created by Goodecheeseburgers on 20/04/2020.
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

#include "Enemy.h"


// Constructor
Enemy::Enemy(sf::RenderTarget &target, int type) {
    this->color = {};
    this->type = type;
    this->velocityY = {};

    this->initAttributes();

    // Set the enemy position
    this->shape.setPosition(
            static_cast<float>(rand() % static_cast<int>(target.getSize().x - shape.getSize().x)),
            0.F
    );
}

// ---------------------------------------------------------------------------------------------------------------------
Enemy::~Enemy() = default;

// Methods -------------------------------------------------------------------------------------------------------------
void Enemy::initAttributes() {
    switch (this->type) {
        case 0:
            this->color = sf::Color::Cyan;
            this->size = sf::Vector2f(100.f, 100.f);
            this->velocityY = 5.F;
            break;
        case 1:
            this->color = sf::Color::Green;
            this->size = sf::Vector2f(80.f, 80.f);
            this->velocityY = 5.F;
            break;
        case 2:
            this->color = sf::Color::Red;
            this->size = sf::Vector2f(70.f, 70.f);
            this->velocityY = 4.7F;
            break;
        case 3:
            this->color = sf::Color::Yellow;
            this->size = sf::Vector2f(50.f, 50.f);
            this->velocityY = 4.5F;
            break;
        case 4:
            this->color = sf::Color::Magenta;
            this->size = sf::Vector2f(30.f, 30.f);
            this->velocityY = 4.F;
            break;
        default:
            std::cout << "ERROR::ENEMY::INITATTRIBUTES: No such type\n";
            break;

    }

    // Set initial size
    this->shape.setSize(this->size);
    // Set initial fill colour
    this->shape.setFillColor(this->color);
}

// ---------------------------------------------------------------------------------------------------------------------
void Enemy::update() {
    this->posY -= this->velocityY;

    this->shape.move(0.F, this->velocityY);
}

// ---------------------------------------------------------------------------------------------------------------------
void Enemy::render(sf::RenderTarget &target) const {
    target.draw(this->shape);
}
// --------------------------------------------------------------------------------------------------------------------
